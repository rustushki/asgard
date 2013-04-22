/*****************************************************************************
 * Copyright (c) 2013 Russ Adams, Sean Eubanks, Asgard Contributors
 * This file is part of Asgard.
 * 
 * Asgard is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asgard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with Asgard; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/

#include "MapObjectFactory.h"

sqlite3* MapObjectFactory::db = NULL;

bool MapObjectFactory::build(sqlite3 *db, int boxX, int boxY) {
   char *query;
   sqlite3_stmt *stmt;

   MapObjectFactory::db = db;

   // Invalid Bounding Box
   if (boxX < 0 || boxY < 0)
      return false;

   // Build NonPlayerCharacters
   query = QueryGenerator::nonPlayerCharacter(boxX, boxY);
   LOG(INFO) << "NonPlayerCharacter query: " << query;
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW) {
      createNonPlayerCharacter(db, stmt);
   }
   sqlite3_finalize(stmt);
   delete [] query;
  
   // Build Containers
   query = QueryGenerator::container(boxX, boxY);
   LOG(INFO) << "Container query: " << query;
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW) {
      createContainer(db, stmt);
   }
   sqlite3_finalize(stmt);
   delete [] query;

   // Build MapObjects
   query = QueryGenerator::mapObject(boxX, boxY);
   LOG(INFO) << "MapObject query: " << query;
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW) {
      createMapObject(db, stmt);
   }
   sqlite3_finalize(stmt);
   delete [] query;

   // Build Tiles
   query = QueryGenerator::tile(boxX, boxY);
   LOG(INFO) << "Tile query: " << query;
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW) {
      createTile(stmt);
   }
   sqlite3_finalize(stmt);
   delete [] query;

   return true;
}

void MapObjectFactory::createTile(sqlite3_stmt *stmt) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, TILE_COLUMN_DRAWABLE_NAME)
   );

   // Create new tile
   Tile *tile = NULL;
  
   TileType tileType = (TileType)sqlite3_column_int(stmt, TILE_COLUMN_TILE_TYPE);

   switch(tileType) {
      case TILE_TYPE_WATER:   { tile = new WaterTile(drawable); break; }
      case TILE_TYPE_DESERT:  { tile = new DesertTile(drawable); break; }
      case TILE_TYPE_GRASS:   { tile = new GrassTile(drawable); break; }
      default:                { break; }
   }

   if(tile != NULL) {
      // Set Tile Map Object attributes
      tile->setLeftCorner(Coordinate<MapPoint>(sqlite3_column_int(stmt, TILE_COLUMN_WC_X), sqlite3_column_int(stmt, TILE_COLUMN_WC_Y)));
      Map::getInstance()->installMapObject(tile, drawable);
   }
}

void MapObjectFactory::createContainer(sqlite3 *db, sqlite3_stmt *stmt) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, CONTAINER_COLUMN_DRAWABLE_NAME)
   );

   int mapObjectId = sqlite3_column_int(stmt, CONTAINER_COLUMN_MAP_OBJECT_ID);
   int inventoryId = sqlite3_column_int(stmt, CONTAINER_COLUMN_INVENTORY_ID);

   // Create Inventory
   Inventory inv;
   RowSet* rs = loadInventory(db, inventoryId);
   if (rs != NULL) {
      for (int row = 0; row < rs->getRowCount(); row++) {
         std::string itemName = rs->getColumnValue(row,INVENTORY_COLUMN_ITEMNAME);
         int quantity = atoi(rs->getColumnValue(row,INVENTORY_COLUMN_QUANTITY));

         while(quantity > 0) {
            inv.addItem(Item(itemName));
            quantity--;
         }
      }
   }
   delete rs;

   Container* container = new Container(drawable, inv);

   std::cout << "loading container" << std::endl;

   if (container != NULL) {

      addInteractions(db, (MapObject*) container, mapObjectId);
      addHardpoints(db, (MapObject*) container, mapObjectId);

      // Set Container attributes
      container->setLeftCorner(Coordinate<MapPoint>(sqlite3_column_int(stmt, CONTAINER_COLUMN_WC_X), sqlite3_column_int(stmt, CONTAINER_COLUMN_WC_Y)));
      Map::getInstance()->installMapObject(container, drawable);
   }

}

void MapObjectFactory::createNonPlayerCharacter(sqlite3 *db, sqlite3_stmt *stmt) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, NON_PLAYER_CHARACTER_COLUMN_DRAWABLE_NAME)
   );

   NonPlayerCharacter *npc = new NonPlayerCharacter(drawable);

   if (npc != NULL) {

      int mapObjectId = sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID);

      addHardpoints(db, (MapObject*) npc, mapObjectId);

      // Create NonPlayerCharacterPath
      RowSet *rs = loadNonPlayerCharacterPath(db, mapObjectId);

      if (rs != NULL) {
         for (int row = 0; row < rs->getRowCount(); row++)
            npc->addCoordinateToPath(createNonPlayerCharacterPathPoint(rs,row));
      }

      npc->setLeftCorner(Coordinate<MapPoint>(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WC_X), sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WC_Y)));
      Map::getInstance()->installMapObject(npc, drawable);
        
      delete rs;
   }
}

void MapObjectFactory::createMapObject(sqlite3 *db, sqlite3_stmt *stmt) {

   // No starter MapObject to pass in.
   MapObjectFactory::createMapObject(db, stmt, NULL);

}

void MapObjectFactory::createMapObject(sqlite3 *db, sqlite3_stmt *stmt, MapObject *mo) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, MAP_OBJECT_COLUMN_DRAWABLE_NAME)
   );

   MapObject *mapObject = new MapObject(drawable);

   if (mapObject != NULL) {

      int mapObjectId = sqlite3_column_int(stmt, MAP_OBJECT_COLUMN_MAP_OBJECT_ID);

      addInteractions(db, mapObject, mapObjectId);
      addHardpoints(db, mapObject, mapObjectId);

      mapObject->setLeftCorner(Coordinate<MapPoint>(sqlite3_column_int(stmt, MAP_OBJECT_COLUMN_WC_X), sqlite3_column_int(stmt, MAP_OBJECT_COLUMN_WC_Y)));
      Map::getInstance()->installMapObject(mapObject, drawable);
   }
}

void MapObjectFactory::addHardpoints(sqlite3 *db, MapObject *mo, int mapObjectId) { 
   // Create Hardpoints
   RowSet *rs = loadHardpoints(db, mapObjectId);

   if (rs != NULL) {
      for (int row = 0; row < rs->getRowCount(); row++)
         mo->addHardpoint(createHardpoint(rs,row));
   }
   delete rs;
}

void MapObjectFactory::addInteractions(sqlite3 *db, MapObject *mo, int mapObjectId) {

   RowSet* rs;

   // Create Interactionpoints
   rs = loadInteractionpoints(db, mapObjectId);

   if (rs != NULL) {
      for (int row = 0; row < rs->getRowCount(); row++) {
         mo->addInteractionpoint(createInteractionpoint(rs,row));
      }
   }
   delete rs;


   // Create AnimationInteractions
   rs = loadInteractions(db, mapObjectId, INTERACTION_TYPE_ANIMATION);
   if (rs != NULL) {
      for (int row = 0; row < rs->getRowCount(); row++) {
         mo->addInteraction(createInteraction(rs,row,INTERACTION_TYPE_ANIMATION));
      }
   }
   delete rs;

   // Create ItemInteractions
   rs = loadInteractions(db, mapObjectId, INTERACTION_TYPE_ITEM);
   if (rs != NULL) {
      for (int row = 0; row < rs->getRowCount(); row++) {
         std::cout << "item interaction" << std::endl;
         mo->addInteraction(createInteraction(rs,row,INTERACTION_TYPE_ITEM));
      }
   }
   delete rs;

   // Create DialogInteractions
   rs = loadInteractions(db, mapObjectId, INTERACTION_TYPE_DIALOG);
   if (rs != NULL) {
      for (int row = 0; row < rs->getRowCount(); row++) {
         mo->addInteraction(createInteraction(rs,row,INTERACTION_TYPE_DIALOG));
      }
   }
   delete rs;
}

Hardpoint* MapObjectFactory::createHardpoint(RowSet* rs, int row) {
      // Rect and Circ Hardpoints need these.
      int type = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_HARDPOINT_TYPE));
      int x = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_RELATIVE_X));
      int y = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_RELATIVE_Y));

      // Only RectHardpoints
      if (type == HARDPOINT_TYPE_RECT) {
         int height = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_HEIGHT));
         int width = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_WIDTH));
         return new RectHardpoint(x,y,height,width);

      // Only CircHardpoints
      } else if (type == HARDPOINT_TYPE_CIRC) {
         double r = atof(rs->getColumnValue(row,HARDPOINT_COLUMN_RADIUS));
         return new CircHardpoint(x,y,r);

      // Default 
      } else {
         return new RectHardpoint();
      }
}

Interactionpoint* MapObjectFactory::createInteractionpoint(RowSet* rs, int row) {
      // Rect and Circ Interactionpoints need these.
      int type = atoi(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_INTERACTIONPOINT_TYPE));
      int x = atoi(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_RELATIVE_X));
      int y = atoi(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_RELATIVE_Y));
      bool requiresMouseClick = atoi(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_REQUIRES_MOUSE_CLICK)) != 0;

      // Only RectInteractionpoints
      if (type == INTERACTIONPOINT_TYPE_RECT) {
         int height = atoi(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_HEIGHT));
         int width = atoi(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_WIDTH));
         return new RectInteractionpoint(x,y,height,width,requiresMouseClick);

      // Only CircInteractionpoints
      } else if (type == INTERACTIONPOINT_TYPE_CIRC) {
         double r = atof(rs->getColumnValue(row,INTERACTIONPOINT_COLUMN_RADIUS));
         return new CircInteractionpoint(x,y,r,requiresMouseClick);

      // Default
      } else {
         return new RectInteractionpoint();
      }
}

Interaction* MapObjectFactory::createInteraction(RowSet* rs, int row, int interactionType) {
   // Priority column value is same for each interaction type
   int priority = atoi(rs->getColumnValue(row,INTERACTION_COLUMN_PRIORITY));
   // isHandledOnce column value is same for each interaction type
   bool isHandledOnce = atoi(rs->getColumnValue(row,INTERACTION_COLUMN_IS_HANDLED_ONCE)) != 0;

   // AnimationInteractions
   switch (interactionType) {
      // AnimationInteractions
      case INTERACTION_TYPE_ANIMATION:
         return new AnimationInteraction(priority, isHandledOnce, rs->getColumnValue(row,ANIMATION_INTERACTION_COLUMN_ANIMATION_NAME));
         break;
      // ItemInteractions
      case INTERACTION_TYPE_ITEM:
         return new ItemInteraction(priority, isHandledOnce, rs->getColumnValue(row,ITEM_INTERACTION_COLUMN_ITEM_NAME));
         break;
      // DialogInteractions
      case INTERACTION_TYPE_DIALOG:
         return new DialogInteraction(priority, isHandledOnce, rs->getColumnValue(row,DIALOG_INTERACTION_COLUMN_TEXT));
         break;
      default:
         std::cout<<"ERROR:  Undefined Interaction Type!"<<std::endl;
         return 0;
   }
}

Coordinate<MapPoint>* MapObjectFactory::createNonPlayerCharacterPathPoint(RowSet* rs, int row) {
   int wc_x,wc_y = 0;

   wc_x = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_X));
   wc_y = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_Y));

   return new Coordinate<MapPoint>(wc_x, wc_y);
}

RowSet* MapObjectFactory::loadInventory(sqlite3 *db, int inventoryId) {
   RowSet* rs = new RowSet();
   char* invQuery;
   int rc;
 
   invQuery = QueryGenerator::inventory(inventoryId);
   rc = rs->select(db, invQuery);
   delete [] invQuery;

   if (rc == SQLITE_OK) {
      assert(rs->getColCount() == INVENTORY_COLUMN_COUNT);
   }

   return rs;

}

RowSet* MapObjectFactory::loadHardpoints(sqlite3 *db, int smoId) {
   RowSet* rs = new RowSet();
   char* hpQuery;
   int rc;
 
   hpQuery = QueryGenerator::hardpoint(smoId);
   rc = rs->select(db, hpQuery);
   delete [] hpQuery;

   if (rc == SQLITE_OK) {
      assert(rs->getColCount() == HARDPOINT_COLUMN_COUNT);
   }

   return rs;
}

RowSet* MapObjectFactory::loadInteractionpoints(sqlite3 *db, int smoId) {
   RowSet* rs = new RowSet();
   char* ipQuery;
   int rc;
 
   ipQuery = QueryGenerator::interactionpoint(smoId);
   rc = rs->select(db, ipQuery);
   delete [] ipQuery;

   // If no rows returned, no columns returned
   if ((rc == SQLITE_OK) && (rs->getRowCount() > 0)) {
      assert(rs->getColCount() == INTERACTIONPOINT_COLUMN_COUNT);
   }

   return rs;
}

RowSet* MapObjectFactory::loadInteractions(sqlite3 *db, int smoId, int interactionType) {
   RowSet* rs = new RowSet();
   char* iQuery;
   int rc;
 
   switch (interactionType) {
      // Load AnimationInteractions
      case INTERACTION_TYPE_ANIMATION:
         iQuery = QueryGenerator::animationInteraction(smoId,interactionType);
         rc = rs->select(db, iQuery);
         delete [] iQuery;

         // If no rows returned, no columns returned
         if ((rc == SQLITE_OK) && (rs->getRowCount() > 0)) {
            assert(rs->getColCount() == ANIMATION_INTERACTION_COLUMN_COUNT);
         }
         break;
      // Load ItemInteractions
      case INTERACTION_TYPE_ITEM:
         iQuery = QueryGenerator::itemInteraction(smoId,interactionType);
         rc = rs->select(db, iQuery);
         delete [] iQuery;

         // If no rows returned, no columns returned
         if ((rc == SQLITE_OK) && (rs->getRowCount() > 0)) {
            assert(rs->getColCount() == ITEM_INTERACTION_COLUMN_COUNT);
         }
         break;
      // Load DialogInteractions
      case INTERACTION_TYPE_DIALOG:
         iQuery = QueryGenerator::dialogInteraction(smoId,interactionType);
         rc = rs->select(db, iQuery);
         delete [] iQuery;

         // If no rows returned, no columns returned
         if ((rc == SQLITE_OK) && (rs->getRowCount() > 0)) {
            assert(rs->getColCount() == DIALOG_INTERACTION_COLUMN_COUNT);
         }
         break;
      default:
         iQuery = 0;
   }

   return rs;
}

RowSet* MapObjectFactory::loadNonPlayerCharacterPath(sqlite3 *db, int npcId) {
   RowSet* rs = new RowSet();
   char* npcPathQuery;
   int rc;

   npcPathQuery = QueryGenerator::nonPlayerCharacterPath(npcId);
   rc = rs->select(db, npcPathQuery);
   delete [] npcPathQuery;

   if (rc == SQLITE_OK) {
      assert(rs->getColCount() == NON_PLAYER_CHARACTER_PATH_COLUMN_COUNT);
   }

   return rs;
}
