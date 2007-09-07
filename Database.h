/*****************************************************************************
 * Copyright (c) 2006 Russ Adams, Sean Eubanks, Asgard Contributors
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

#include <sqlite3.h>
#include "Coordinate.h"
 
#define ASGARD_DATABASE "asgard.db3"
 
class Database
{
   private:
      Database();
      ~Database();
      sqlite3 *asgardDb;
      static Database* instance;
      
   public:
      static Database* getInstance();
      void determineVisibleBoxes(Coordinate currentPosition, int *visibleBoxes, int numVisibleBoxes);
      bool loadBoundingBox(int boxId);
      char*** loadHardpoints(int smoId);
      char*** loadNonPlayerCharacterPath(int npcId);
      
};

#endif //DATABASE_H

