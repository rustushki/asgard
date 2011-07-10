#include "GameEngine.h"

GameEngine* GameEngine::instance = NULL;


GameEngine* GameEngine::getInstance()
{
   if(instance == NULL) instance = new GameEngine();
   return instance;
}


GameEngine::GameEngine()
{
}


void GameEngine::loadGame()
{
}

void GameEngine::loadVisibleBoxes()
{
   Database* db = Database::getInstance();
   db->determineVisibleBoxes(this->currentPosition,this->visibleBoxes,VISIBLE_BOUNDING_BOXES);

   for (int slot = 0; slot < VISIBLE_BOUNDING_BOXES; slot++)
      db->loadBoundingBox(this->visibleBoxes[slot]);
}


void GameEngine::addMapObject(MapObject* object)
{
   delete object;
}


void GameEngine::removeBoundingBoxObjects(int boundingBoxID)
{
}

