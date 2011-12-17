/*****************************************************************************
 * Copyright (c) 2007 Russ Adams, Sean Eubanks, Asgard Contributors
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

   // Build StaticMapObjects
   query = QueryGenerator::staticMapObject(boxX, boxY);
   LOG(INFO) << "StaticMapObject query: " << query;
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW) {
      createStaticMapObject(db, stmt);
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

   std::string drawableName = drawable->getInstanceName();

   // Create new tile
   Tile *tile = NULL;
  
   TileType tileType = (TileType)sqlite3_column_int(stmt, TILE_COLUMN_TILE_TYPE);

   switch(tileType)
   {
      case TILE_TYPE_WATER:   { tile = new WaterTile(drawableName); break; }
      case TILE_TYPE_DESERT:  { tile = new DesertTile(drawableName); break; }
      case TILE_TYPE_GRASS:   { tile = new GrassTile(drawableName); break; }
      default:                { break; }
   }

   if(tile != NULL)
   {
      // Set Tile Map Object attributes
      tile->setLeftCorner(Coordinate(sqlite3_column_int(stmt, TILE_COLUMN_WC_X), sqlite3_column_int(stmt, TILE_COLUMN_WC_Y)));
      tile->setWidth(sqlite3_column_int(stmt, TILE_COLUMN_WIDTH));
      tile->setHeight(sqlite3_column_int(stmt, TILE_COLUMN_HEIGHT));
      Map::getInstance()->installMapObject(tile, drawable);
   }
}

void MapObjectFactory::createContainer(sqlite3 *db, sqlite3_stmt *stmt) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, CONTAINER_COLUMN_DRAWABLE_NAME)
   );

   std::string drawableName = drawable->getInstanceName();

   Container* container = new Container(drawableName);

   // Create Hardpoints
   RowSet* rs = loadHardpoints(db, sqlite3_column_int(stmt, CONTAINER_COLUMN_MAP_OBJECT_ID));

   if (rs != NULL)
   {
      for (int row = 0; row < rs->getRowCount(); row++)
         container->addHardpoint(createHardpoint(rs,row));
   }
   delete rs;

   // TODO: Create Items; Not 0.3.0
  

   if (container != NULL)
   {
      // Set Container attributes
      container->setLeftCorner(Coordinate(sqlite3_column_int(stmt, CONTAINER_COLUMN_WC_X), sqlite3_column_int(stmt, CONTAINER_COLUMN_WC_Y)));
      container->setWidth(sqlite3_column_int(stmt, CONTAINER_COLUMN_WIDTH));
      container->setHeight(sqlite3_column_int(stmt, CONTAINER_COLUMN_HEIGHT));
      Map::getInstance()->installMapObject(container, drawable);
   }

}

void MapObjectFactory::createNonPlayerCharacter(sqlite3 *db, sqlite3_stmt *stmt) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, NON_PLAYER_CHARACTER_COLUMN_DRAWABLE_NAME)
   );

   std::string drawableName = drawable->getInstanceName();

   NonPlayerCharacter *npc = new NonPlayerCharacter(drawableName);
  
   if (npc != NULL)
   {
      // Create Hardpoints
      RowSet* hpRs = loadHardpoints(db, sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID));

      if (hpRs != NULL)
      {
         for (int row = 0; row < hpRs->getRowCount(); row++)
            npc->addHardpoint(createHardpoint(hpRs,row));
      }

      delete hpRs;

      // Create NonPlayerCharacterPath
      RowSet* npcRs = loadNonPlayerCharacterPath(db, sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID));

      if (npcRs != NULL)
      {
         for (int row = 0; row < npcRs->getRowCount(); row++)
            npc->addCoordinateToPath(createNonPlayerCharacterPathPoint(npcRs,row));
      }
     
      npc->setLeftCorner(Coordinate(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WC_X), sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WC_Y)));
      npc->setWidth(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WIDTH));
      npc->setHeight(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_HEIGHT));
      Map::getInstance()->installMapObject(npc, drawable);
        
      delete npcRs;
   }
}

void MapObjectFactory::createStaticMapObject(sqlite3 *db, sqlite3_stmt *stmt) {
   Drawable* drawable = DrawableFactory::build(
        MapObjectFactory::db
	  , (const char *)sqlite3_column_text(stmt, STATIC_MAP_OBJECT_COLUMN_DRAWABLE_NAME)
   );

   std::string drawableName = drawable->getInstanceName();

   StaticMapObject *staticMapObject = new StaticMapObject(drawableName);

   if (staticMapObject != NULL)
   {
      // Create Hardpoints
      RowSet* rs = loadHardpoints(db, sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_MAP_OBJECT_ID));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            staticMapObject->addHardpoint(createHardpoint(rs,row));
      }
      delete rs;

      staticMapObject->setLeftCorner(Coordinate(sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_WC_X), sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_WC_Y)));
      staticMapObject->setWidth(sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_WIDTH));
      staticMapObject->setHeight(sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_HEIGHT));
      Map::getInstance()->installMapObject(staticMapObject, drawable);
   }
}

Hardpoint* MapObjectFactory::createHardpoint(RowSet* rs, int row) {
      int x,y,height,width,type = 0;
      double r = 0;

      // Rect and Circ Hardpoints need these.
      type = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_HARDPOINT_TYPE));
      x = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_RELATIVE_X));
      y = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_RELATIVE_Y));

      // Only RectHardpoints
      if (type == HARDPOINT_TYPE_RECT)
      {
         height = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_WIDTH));
         width = atoi(rs->getColumnValue(row,HARDPOINT_COLUMN_HEIGHT));
         return new RectHardpoint(x,y,height,width);
      }
      // Only CircHardpoints
      else if (type == HARDPOINT_TYPE_CIRC)
      {
         r = atof(rs->getColumnValue(row,HARDPOINT_COLUMN_RADIUS));
         return new CircHardpoint(x,y,type);
      }
      // Default
      else
      {
         return new RectHardpoint();
      }
}

Coordinate* MapObjectFactory::createNonPlayerCharacterPathPoint(RowSet* rs, int row) {
   int wc_x,wc_y = 0;

   wc_x = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_X));
   wc_y = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_Y));

   return new Coordinate(wc_x, wc_y);
}

RowSet* MapObjectFactory::loadHardpoints(sqlite3 *db, int smoId) {
   RowSet* rs = new RowSet();
   char* hpQuery;
   int rc;
 
   hpQuery = QueryGenerator::hardpoint(smoId);
   rc = rs->select(db, hpQuery);
   delete [] hpQuery;

   if (rc == SQLITE_OK)
   {
      assert(rs->getColCount() == HARDPOINT_COLUMN_COUNT);
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

   if (rc == SQLITE_OK)
   {
      assert(rs->getColCount() == NON_PLAYER_CHARACTER_PATH_COLUMN_COUNT);
   }

   return rs;
}
