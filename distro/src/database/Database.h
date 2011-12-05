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
 
#ifndef DATABASE_H
#define DATABASE_H

#include "externals.h"
#include "SystemComponent.h"
#include "Coordinate.h"
#include "MapObjectFactory.h"
#include "MessageFactory.h"
#include "DrawableFactory.h"
 
class Database : public SystemComponent
{
   private:
      Database();
      ~Database();
      sqlite3 *asgardDb;
      static Database* instance;
      
      void loop();
      virtual bool interpretMessage(Message* message);
      std::string getDatabasePath();

   public:
      static Database* getInstance();
      sqlite3* getAsgardDb() const;

      void determineVisibleBoxes(Coordinate currentPosition, int *visibleBoxes, int numVisibleBoxes);
      bool loadBoundingBox(int boxX, int boxY);
      bool loadDrawable(std::string dName);
      
      virtual bool open();
      virtual bool close();
};

#endif //DATABASE_H
