/*****************************************************************************
 * Copyright (c) 2011 Russ Adams, Sean Eubanks, Asgard Contributors
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

#include "Database.h"
#include "consts.h"

Database* Database::instance = NULL;

Database::Database() {
   std::string path = this->getDatabasePath();
   int status = sqlite3_open(path.c_str(), &this->asgardDb);
   
   if(status != SQLITE_OK)
   {
      sqlite3_close(this->asgardDb);
   }

   // TODO: Add some type of logging for status
}

Database::~Database() {
   sqlite3_close(this->asgardDb);
}

Database* Database::getInstance() {
   if(instance == NULL) instance = new Database();
   return instance;
}

sqlite3* Database::getAsgardDb() const {
   return this->asgardDb;
}

/* Gets the path to the database. Uses RES resource path from consts.h
 *
 * @return std::string - path to database.
 * @access private
 */
std::string Database::getDatabasePath() {
   std::string path(RES);
   path.append("database/asgard.db3");
   return path;
}

bool Database::loadBoundingBox(int boxX, int boxY) {
   MapObjectFactory::build(this->asgardDb, boxX, boxY);
   return true;
}

bool Database::loadDrawable(std::string dName) {
   DrawableFactory::build(this->asgardDb, dName);
   return true;
}

/*
bool Database::interpretMessage(Message* msg) {
   bool messageHandled = false;
   std::string printOutput;

   if (msg->header.type == MESSAGE_TYPE_LOAD_BOUNDING_BOX)
   {
      if (this->loadBoundingBox(msg->data.box.X, msg->data.box.Y))
         printOutput = "bounding box loaded";
      else
         printOutput = "failed";

      MessageFactory::makePrintString(printOutput.c_str());
      messageHandled = true;
   }

   else if (msg->header.type == MESSAGE_TYPE_LOAD_DRAWABLE)
   {
      std::string dName(msg->data.loadDrawable.drawableName);

      if (dName.empty())
         printOutput = "Failed: no drawable name provided";
      else if (this->loadDrawable(dName))
         printOutput = "drawable loaded";

      MessageFactory::makePrintString(printOutput.c_str());
      messageHandled = true;
   }
   return messageHandled;
}
*/
