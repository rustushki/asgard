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
   Container *container = new Container();
   
   // TODO: Add all columnValue data to Container object
   
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
