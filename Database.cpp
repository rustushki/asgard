#include "Database.h"
#include "MapObjectFactory.h"
#include "MapObjectType.h"
#include "QueryGenerator.h"

Database::Database()
{
   int status = sqlite3_open(ASGARD_DATABASE, &this->asgardDb);
   
   if(status != SQLITE_OK)
   {
      sqlite3_close(this->asgardDb);
   }
   
   // TODO: Add some type of logging for status
}

Database::~Database()
{
   sqlite3_close(this->asgardDb);
}

void Database::determineVisibleBoxes(Coordinate currentPosition, int *visibleBoxes, int numVisibleBoxes)
{
}

bool Database::loadBoundingBox(int boxId)
{
   char **sqliteErrorCode;

   sqlite3_exec(this->asgardDb, QueryGenerator::container(boxId), MapObjectFactory::processRow, (void*)(MAP_OBJECT_TYPE_CONTAINER), sqliteErrorCode);
   sqlite3_exec(this->asgardDb, QueryGenerator::nonPlayerCharacter(boxId), MapObjectFactory::processRow, (void*)MAP_OBJECT_TYPE_NON_PLAYER_CHARACTER, sqliteErrorCode);
   sqlite3_exec(this->asgardDb, QueryGenerator::staticMapObject(boxId), MapObjectFactory::processRow, (void*)MAP_OBJECT_TYPE_STATIC_MAP_OBJECT, sqliteErrorCode);
   sqlite3_exec(this->asgardDb, QueryGenerator::tile(boxId), MapObjectFactory::processRow, (void*)MAP_OBJECT_TYPE_TILE, sqliteErrorCode);
   
   return true;
}