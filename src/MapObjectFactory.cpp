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
#include "GameEngine.h"
#include "Tile.h"
#include "WaterTile.h"
#include "GrassTile.h"
#include "DesertTile.h"
#include "Container.h"
#include "StaticMapObject.h"
#include "NonPlayerCharacter.h"
#include "MapObjectType.h"
#include "DatabaseColumnMap.h"
#include "Hardpoint.h"
#include "CircHardpoint.h"
#include "RectHardpoint.h"
#include "Database.h"

int MapObjectFactory::processRow(void *mapObjectType, int columnCount, char **columnValue, char **columnName)
{
   MapObjectType *type = static_cast<MapObjectType*>(mapObjectType);

   switch(*type)
   {
      case MAP_OBJECT_TYPE_CONTAINER:              { MapObjectFactory::createContainer(columnValue); break; }
      case MAP_OBJECT_TYPE_NON_PLAYER_CHARACTER:   { MapObjectFactory::createNonPlayerCharacter(columnValue); break; }
      case MAP_OBJECT_TYPE_STATIC_MAP_OBJECT:      { MapObjectFactory::createStaticMapObject(columnValue); break; }
      case MAP_OBJECT_TYPE_TILE:                   { MapObjectFactory::createTile(columnValue); break; }
      default:                                     { /* TODO: Error case... add logging */ break; }
   }
   
   
   return 0;
}


void MapObjectFactory::createTile(char **columnValue)
{
   // Create new tile
   Tile *tile;
      
   // MapObject Req'd Members
   int wc_x;
   int wc_y;
   int height;
   int width;
   
   TileType tileType = (TileType)atoi(columnValue[TILE_COLUMN_TILE_TYPE]);
   
   switch(tileType)
   {
      case TILE_TYPE_WATER:   { tile = new WaterTile(); break; }
      case TILE_TYPE_DESERT:  { tile = new DesertTile(); break; }
      case TILE_TYPE_GRASS:   { tile = new GrassTile(); break; }
      default:                { break; }
   }

   if(tile != NULL)
   {
      wc_x = atoi(columnValue[TILE_COLUMN_WC_X]);
      wc_y = atoi(columnValue[TILE_COLUMN_WC_Y]);
      width = atoi(columnValue[TILE_COLUMN_WIDTH]);
      height = atoi(columnValue[TILE_COLUMN_HEIGHT]);

      // Set tile Map Object variables
      tile->setLeftCorner(Coordinate(wc_x, wc_y));
      tile->setWidth(width);
      tile->setHeight(height);
      
      // Get reference to GameEngine
      GameEngine *gameEngine = GameEngine::getInstance();
      
      // Add tile to gameEngine
      gameEngine->addMapObject((MapObject*)tile);
   }
      
}


void MapObjectFactory::createContainer(char **columnValue)
{
   Database* db = Database::getInstance();
   RowSet* rs;

   // MapObject Req'd Members
   int wc_x;
   int wc_y;
   int height;
   int width;

   // Objects to Create
   Container* container = new Container();

   // Create Hardpoints
   rs = db->loadHardpoints(atoi(columnValue[CONTAINER_COLUMN_MAP_OBJECT_ID]));

   if (rs != NULL)
   {
      for (int row = 0; row < rs->getRowCount(); row++)
         container->addHardpoint(createHardpoint(rs,row));
   }


   // TODO: Create Items; Not 0.3.0
   

   if (container != NULL)
   {
      // Set MapObject Members 
      wc_x = atoi(columnValue[CONTAINER_COLUMN_WC_X]);
      wc_y = atoi(columnValue[CONTAINER_COLUMN_WC_Y]);
      width = atoi(columnValue[CONTAINER_COLUMN_WIDTH]);
      height = atoi(columnValue[CONTAINER_COLUMN_HEIGHT]);

      container->setLeftCorner(Coordinate(wc_x, wc_y));
      container->setWidth(width);
      container->setHeight(height);

      // Get reference to GameEngine
      GameEngine *gameEngine = GameEngine::getInstance();
         
      // Add container to gameEngine
      gameEngine->addMapObject((MapObject*)container);
   }
}


void MapObjectFactory::createNonPlayerCharacter(char **columnValue)
{
   Database* db = Database::getInstance();
   RowSet* rs;

   // MapObject Req'd Members
   int wc_x;
   int wc_y;
   int height;
   int width;

   NonPlayerCharacter *npc = new NonPlayerCharacter();
   
   if (npc != NULL)
   {
      // Create Hardpoints
      rs = db->loadHardpoints(atoi(columnValue[NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID]));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            npc->addHardpoint(createHardpoint(rs,row));
      }

      // Create NonPlayerCharacterPath
      rs = db->loadNonPlayerCharacterPath(atoi(columnValue[NON_PLAYER_CHARACTER_COLUMN_MAP_OBJECT_ID]));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            npc->addCoordinateToPath(createNonPlayerCharacterPathPoint(rs,row));
      }
      
      wc_x = atoi(columnValue[NON_PLAYER_CHARACTER_COLUMN_WC_X]);
      wc_y = atoi(columnValue[NON_PLAYER_CHARACTER_COLUMN_WC_Y]);
      width = atoi(columnValue[NON_PLAYER_CHARACTER_COLUMN_WIDTH]);
      height = atoi(columnValue[NON_PLAYER_CHARACTER_COLUMN_HEIGHT]);

      npc->setLeftCorner(Coordinate(wc_x, wc_y));
      npc->setWidth(width);
      npc->setHeight(height);

      // Get reference to GameEngine
      GameEngine *gameEngine = GameEngine::getInstance();
         
      // Add container to gameEngine
      gameEngine->addMapObject((MapObject*)npc);
   }
}


void MapObjectFactory::createStaticMapObject(char **columnValue)
{
   Database* db = Database::getInstance();
   RowSet* rs;
   
   // MapObject Req'd Members
   int wc_x;
   int wc_y;
   int height;
   int width;

   StaticMapObject *staticMapObject = new StaticMapObject();

   if (staticMapObject != NULL)
   {
      // Create Hardpoints
      rs = db->loadHardpoints(atoi(columnValue[STATIC_MAP_OBJECT_COLUMN_MAP_OBJECT_ID]));

      if (rs != NULL)
      {
         for (int row = 0; row < rs->getRowCount(); row++)
            staticMapObject->addHardpoint(createHardpoint(rs,row));
      }

      wc_x = atoi(columnValue[STATIC_MAP_OBJECT_COLUMN_WC_X]);
      wc_y = atoi(columnValue[STATIC_MAP_OBJECT_COLUMN_WC_Y]);
      width = atoi(columnValue[STATIC_MAP_OBJECT_COLUMN_WIDTH]);
      height = atoi(columnValue[STATIC_MAP_OBJECT_COLUMN_HEIGHT]);

      staticMapObject->setLeftCorner(Coordinate(wc_x, wc_y));
      staticMapObject->setWidth(width);
      staticMapObject->setHeight(height);

      // Get reference to GameEngine
      GameEngine *gameEngine = GameEngine::getInstance();
         
      // Add container to gameEngine
      gameEngine->addMapObject((MapObject*)staticMapObject);
   }

}


Hardpoint* MapObjectFactory::createHardpoint(RowSet* rs, int row)
{
      int x       = 0;
      int y       = 0;
      int height  = 0;
      int width   = 0;
      double r    = 0;
      int type    = 0;

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
   int wc_x = 0;
   int wc_y = 0;

   wc_x = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_X));
   wc_y = atoi(rs->getColumnValue(row,NON_PLAYER_CHARACTER_PATH_COLUMN_WC_Y));

   return new Coordinate(wc_x, wc_y);
}
