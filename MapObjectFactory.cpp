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
   
   return true;
}

void MapObjectFactory::createTile(char **columnValue)
{
   // Create new tile
   Tile *tile;
   
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
      // Set tile Map Object variables
      tile->setWidth(atoi(columnValue[TILE_COLUMN_WIDTH]));
      tile->setHeight(atoi(columnValue[TILE_COLUMN_HEIGHT]));
      
      // Get reference to GameEngine
      GameEngine *gameEngine = GameEngine::getInstance();
      
      // Add tile to gameEngine
      gameEngine->addMapObject((MapObject*)tile);
   }
      
}

void MapObjectFactory::createContainer(char **columnValue)
{
   Database* db = Database::getInstance();
   char*** table;

   // Objects to Create
   Container* container = new Container();
   Hardpoint* hardpoint; 

   //
   table = db->loadHardpoints(atoi(columnValue[CONTAINER_COLUMN_MAP_OBJECT_ID]));

   
   // Get reference to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
      
   // Add container to gameEngine
   gameEngine->addMapObject((MapObject*)container);
}

void MapObjectFactory::createNonPlayerCharacter(char **columnValue)
{
   NonPlayerCharacter *npc = new NonPlayerCharacter();
   
   // TODO: Add all columnValue data to NonPlayerCharacter object
   
   // Get reference to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
      
   // Add container to gameEngine
   gameEngine->addMapObject((MapObject*)npc);
}

void MapObjectFactory::createStaticMapObject(char **columnValue)
{
   StaticMapObject *staticMapObject = new StaticMapObject();
   
   // TODO: Add all columnValue data to NonPlayerCharacter object
   
   // Get reference to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
      
   // Add container to gameEngine
   gameEngine->addMapObject((MapObject*)staticMapObject);

}
