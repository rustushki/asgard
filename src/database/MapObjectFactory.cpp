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
#include "Tile.h"
#include "WaterTile.h"
#include "GrassTile.h"
#include "DesertTile.h"
#include "Container.h"
#include "StaticMapObject.h"
#include "NonPlayerCharacter.h"
#include "DatabaseColumnMap.h"
#include "CircHardpoint.h"
#include "RectHardpoint.h"
#include "QueryGenerator.h"
#include <cstdlib>

int MapObjectFactory::build(sqlite3 *db, int boxId)
{
   char *query;
   sqlite3_stmt *stmt;

   // Invalid Bounding Box
   if (boxId <= 0)
      return false;

   // Get pointer to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
 
   // Build NonPlayerCharacters
   query = QueryGenerator::nonPlayerCharacter(boxId);
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW)
   {
      createNonPlayerCharacter(db, stmt, gameEngine);
   }
   sqlite3_finalize(stmt);
   delete [] query;
  
   // Build Containers
   query = QueryGenerator::container(boxId);
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW)
   {
      createContainer(db, stmt, gameEngine);
   }
   sqlite3_finalize(stmt);
   delete [] query;

   // Build StaticMapObjects
   query = QueryGenerator::staticMapObject(boxId);
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW)
   {
      createStaticMapObject(db, stmt, gameEngine);
   }
   sqlite3_finalize(stmt);
   delete [] query;

   // Build Tiles
   query = QueryGenerator::tile(boxId);
   stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);
   while (sqlite3_step(stmt) == SQLITE_ROW)
   {
      createTile(stmt, gameEngine);
   }
   sqlite3_finalize(stmt);
   delete [] query;

   return 0;
}

void MapObjectFactory::createTile(sqlite3_stmt *stmt, GameEngine *gameEngine)
{
   // Create new tile
   Tile *tile;
  
   TileType tileType = (TileType)sqlite3_column_int(stmt, TILE_COLUMN_TILE_TYPE);

   switch(tileType)
   {
      case TILE_TYPE_WATER:   { tile = new WaterTile(); break; }
      case TILE_TYPE_DESERT:  { tile = new DesertTile(); break; }
      case TILE_TYPE_GRASS:   { tile = new GrassTile(); break; }
      default:                { break; }
   }

   if(tile != NULL)
   {
      // Set Tile Map Object attributes
      tile->setLeftCorner(Coordinate(sqlite3_column_int(stmt, TILE_COLUMN_WC_X), sqlite3_column_int(stmt, TILE_COLUMN_WC_Y)));
      tile->setWidth(sqlite3_column_int(stmt, TILE_COLUMN_WIDTH));
      tile->setHeight(sqlite3_column_int(stmt, TILE_COLUMN_HEIGHT));

      // Add Tile to gameEngine
      gameEngine->addMapObject((MapObject*)tile);
   }
}

void MapObjectFactory::createContainer(sqlite3 *db, sqlite3_stmt *stmt, GameEngine *gameEngine)
{
   RowSet* rs;
   Container* container = new Container();

   // Create Hardpoints
   rs = loadHardpoints(db, sqlite3_column_int(stmt, CONTAINER_COLUMN_MAP_OBJECT_ID));

   if (rs != NULL)
   {
      for (int row = 0; row < rs->getRowCount(); row++)
         container->addHardpoint(createHardpoint(rs,row));
   }

   // TODO: Create Items; Not 0.3.0
  

   if (container != NULL)
   {
      // Set Container attributes
      container->setLeftCorner(Coordinate(sqlite3_column_int(stmt, CONTAINER_COLUMN_WC_X), sqlite3_column_int(stmt, CONTAINER_COLUMN_WC_Y)));
      container->setWidth(sqlite3_column_int(stmt, CONTAINER_COLUMN_WIDTH));
      container->setHeight(sqlite3_column_int(stmt, CONTAINER_COLUMN_HEIGHT));

      // Add container to gameEngine
      gameEngine->addMapObject((MapObject*)container);
   }
}

void MapObjectFactory::createNonPlayerCharacter(sqlite3 *db, sqlite3_stmt *stmt, GameEngine *gameEngine)
{
   RowSet* rs;
   NonPlayerCharacter *npc = new NonPlayerCharacter();
  
   if (npc != NULL)
   {
      // Create Hardpoints
      rs = loadHardpoints(db, sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            npc->addHardpoint(createHardpoint(rs,row));
      }

      // Create NonPlayerCharacterPath
      rs = loadNonPlayerCharacterPath(db, sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            npc->addCoordinateToPath(createNonPlayerCharacterPathPoint(rs,row));
      }
     
      npc->setLeftCorner(Coordinate(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WC_X), sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WC_Y)));
      npc->setWidth(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_WIDTH));
      npc->setHeight(sqlite3_column_int(stmt, NON_PLAYER_CHARACTER_COLUMN_HEIGHT));
        
      // Add container to gameEngine
      gameEngine->addMapObject((MapObject*)npc);
   }
}

void MapObjectFactory::createStaticMapObject(sqlite3 *db, sqlite3_stmt *stmt, GameEngine *gameEngine)
{
   RowSet* rs;
   StaticMapObject *staticMapObject = new StaticMapObject();

   if (staticMapObject != NULL)
   {
      // Create Hardpoints
      rs = loadHardpoints(db, sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_MAP_OBJECT_ID));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            staticMapObject->addHardpoint(createHardpoint(rs,row));
      }

      staticMapObject->setLeftCorner(Coordinate(sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_WC_X), sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_WC_Y)));
      staticMapObject->setWidth(sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_WIDTH));
      staticMapObject->setHeight(sqlite3_column_int(stmt, STATIC_MAP_OBJECT_COLUMN_HEIGHT));
       
      // Add container to gameEngine
      gameEngine->addMapObject((MapObject*)staticMapObject);
   }
}

Hardpoint* MapObjectFactory::createHardpoint(RowSet* rs, int row)
{
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

Coordinate* MapObjectFactory::createNonPlayerCharacterPathPoint(RowSet* rs, int row)
{
   int wc_x,wc_y = 0;

   wc_x = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_X));
   wc_y = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_Y));

   return new Coordinate(wc_x, wc_y);
}

RowSet* MapObjectFactory::loadHardpoints(sqlite3 *db, int smoId)
{
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

RowSet* MapObjectFactory::loadNonPlayerCharacterPath(sqlite3 *db, int npcId)
{
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
