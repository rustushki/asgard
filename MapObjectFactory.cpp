#include "MapObjectFactory.h"
#include "GameEngine.h"
#include "Tile.h"
//#include "Container.h"
#include "StaticMapObject.h"
#include "NonPlayerCharacter.h"

void MapObjectFactory::processRow(void *resultType, int columnCount, char **columnValue, char **columnName)
{
   // TODO: Switch on type of result as passed into call back function
      // TODO: Case for each type of database row result that calls a MapObjectFactory private function
}

void MapObjectFactory::createTile(char **columnValue)
{
   // Create new tile
   Tile *tile;
   
   // TODO: Switch on tile type
      // TODO: Create approprate tile subclass

   if(tile != NULL)
   {
      // Get reference to GameEngine
      GameEngine *gameEngine = GameEngine::getInstance();
      
      // Add tile to gameEngine
      gameEngine->addMapObject((MapObject*)tile);
   }
      
}

void MapObjectFactory::createContainer(char **columnValue)
{
   //Container *container = new Container();
   
   // TODO: Add all columnValue data to Container object
   
   // Get reference to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
      
   // Add container to gameEngine
   //gameEngine->addMapObject((MapObject*)container);
}

void MapObjectFactory::createNonPlayerCharacter(char **columnValue)
{
   //NonPlayerCharacter *npc = new NonPlayerCharacter();
   
   // TODO: Add all columnValue data to NonPlayerCharacter object
   
   // Get reference to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
      
   // Add container to gameEngine
   //gameEngine->addMapObject((MapObject*)npc);
}

void MapObjectFactory::createStaticMapObject(char **columnValue)
{
   //StaticMapObject staticMapObject = new StaticMapObject();
   
   // TODO: Add all columnValue data to NonPlayerCharacter object
   
   // Get reference to GameEngine
   GameEngine *gameEngine = GameEngine::getInstance();
      
   // Add container to gameEngine
   //gameEngine->addMapObject((MapObject*)staticMapObject);

}
