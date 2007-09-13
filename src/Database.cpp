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

#include <cassert>
#include "Database.h"
#include "MapObjectFactory.h"
#include "MapObjectType.h"
#include "QueryGenerator.h"
#include "DatabaseColumnMap.h"
#include "GameEngine.h"

Database* Database::instance = NULL;

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

Database* Database::getInstance()
{
   if(instance == NULL) instance = new Database();
   return instance;
}

void Database::determineVisibleBoxes(Coordinate currentPosition, int *visibleBoxes, int numVisibleBoxes)
{
   // Map as of 0.3.0 is 1 boundbox, 0.
   visibleBoxes[0] =  0;
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

char*** Database::loadHardpoints(int smoId, int* rowCount)
{
   char*** table = NULL;
   int* numColumns;
   char** sqliteErrorCode;

   sqlite3_get_table(this->asgardDb, QueryGenerator::hardpoint(smoId), table, rowCount, numColumns, sqliteErrorCode);

   assert(*numColumns == CONTAINER_COLUMN_COUNT);

   return table;
}

char*** Database::loadNonPlayerCharacterPath(int npcId, int* rowCount)
{
   char*** table = NULL;
   int* numColumns;
   char** sqliteErrorCode;

   sqlite3_get_table(this->asgardDb, QueryGenerator::nonPlayerCharacterPath(npcId), table, rowCount, numColumns, sqliteErrorCode);
   
   assert(*numColumns == HARDPOINT_COLUMN_COUNT);

   return table;
}
