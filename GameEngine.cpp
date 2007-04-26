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
   this->database.determineVisibleBoxes(this->currentPosition,this->visibleBoxes,VISIBLE_BOUNDING_BOXES);
}

/*void GameEngine::addMapObject(MapObject object)
{
}*/

void GameEngine::removeBoundingBoxObjects(int boundingBoxID)
{
}



