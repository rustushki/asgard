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

#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <cassert>
#include <string>
#include "Database.h"
#include "MapObjectFactory.h"
#include "MapObjectType.h"
#include "QueryGenerator.h"
#include "DatabaseColumnMap.h"
#include "GameEngine.h"
#include "RowSet.h"
#include "MessageFactory.h"

Database* Database::instance = NULL;

Database::Database() : SystemComponent()
{
   int status = sqlite3_open(ASGARD_DATABASE, &this->asgardDb);
   
   this->thread->name = new char[255];
   this->thread->name = "database";

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
   visibleBoxes[0] =  1;
}

bool Database::loadBoundingBox(int boxId)
{
   char* query;
   MapObjectType type;
   char *sqliteErrorCode;

   // Invalid Bounding Box
   if (boxId <= 0)
      return false;
   
   // NonPlayerCharacter
   query = QueryGenerator::nonPlayerCharacter(boxId);
   type = MAP_OBJECT_TYPE_NON_PLAYER_CHARACTER;
   sqlite3_exec(this->asgardDb, query, MapObjectFactory::processRow, (void*)&type, &sqliteErrorCode);
   delete query;

   // Container
   query = QueryGenerator::container(boxId);
   type = MAP_OBJECT_TYPE_CONTAINER;
   sqlite3_exec(this->asgardDb, query, MapObjectFactory::processRow, (void*)&type, &sqliteErrorCode);
   delete query;

   // StaticMapObject
   query = QueryGenerator::staticMapObject(boxId);
   type = MAP_OBJECT_TYPE_STATIC_MAP_OBJECT;
   sqlite3_exec(this->asgardDb, query, MapObjectFactory::processRow, (void*)&type, &sqliteErrorCode);
   delete query;

   // Tile
   query = QueryGenerator::tile(boxId);
   type = MAP_OBJECT_TYPE_TILE;
   sqlite3_exec(this->asgardDb, query, MapObjectFactory::processRow, (void*)&type, &sqliteErrorCode);
   delete query;

   sqlite3_free(sqliteErrorCode);
   
   return true;
}

RowSet* Database::loadHardpoints(int smoId)
{
   RowSet* rs = new RowSet();
   char* query;
   int rc;

   query = QueryGenerator::hardpoint(smoId);
   rc = rs->select(this->asgardDb, query);
   delete query;

   if (rc == SQLITE_OK)
   {
      assert(rs->getColCount() == HARDPOINT_COLUMN_COUNT);
   }

   return rs;
}

RowSet* Database::loadNonPlayerCharacterPath(int npcId)
{
   RowSet* rs = new RowSet();
   char* query;
   int rc;

   query = QueryGenerator::nonPlayerCharacterPath(npcId);
   rc = rs->select(this->asgardDb, query);
   delete query;

   if (rc == SQLITE_OK)
   {
      assert(rs->getColCount() == NON_PLAYER_CHARACTER_PATH_COLUMN_COUNT);
   }

   return rs;
   
}

bool Database::interpretMessage(Message* msg)
{
   bool messageHandled = false;
   if (msg->header.type == MESSAGE_TYPE_LOAD_BOUNDING_BOX)
   {
      std::string printOutput;

      if (this->loadBoundingBox(msg->data.box.boundingBoxId))
         printOutput = "bounding box loaded";
      else
         printOutput = "failed";

      MessageFactory::makePrintString(printOutput.c_str());
      messageHandled = true;
   }
   return messageHandled;
}

void Database::loop()
{
   while(1)
      this->listen();
}

bool Database::open()
{
   bool status = true;
   
   status = SystemComponent::open();
   
   this->thread->open(boost::bind(&Database::loop, this));
   
   return status;
}

bool Database::close()
{

}
