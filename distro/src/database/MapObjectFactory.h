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

#ifndef MAP_OBJECT_FACTORY_H
#define MAP_OBJECT_FACTORY_H

#include "externals.h"
#include "Coordinate.h"

class Interaction;
class Interactionpoint;
class Hardpoint;
class MapObject;
class MapPoint;
class RowSet;

class MapObjectFactory
{
   private:
      static void createTile(sqlite3_stmt *stmt);
      static void createContainer(sqlite3 *db, sqlite3_stmt *stmt);
      static void createNonPlayerCharacter(sqlite3 *db, sqlite3_stmt *stmt);
      static void createMapObject(sqlite3 *db, sqlite3_stmt *stmt);
      static void createMapObject(sqlite3 *db, sqlite3_stmt *stmt, MapObject* mo);
      static Hardpoint* createHardpoint(RowSet* rs, int row);
      static Interactionpoint* createInteractionpoint(RowSet* rs, int row);
      static Interaction* createInteraction(RowSet* rs, int row, int interactionType);
      static Coordinate<MapPoint>* createNonPlayerCharacterPathPoint(RowSet* rs, int row);
      static void addHardpoints(sqlite3 *db, std::shared_ptr<MapObject> mo, int mapObjectId); 
      static void addInteractions(sqlite3 *db, std::shared_ptr<MapObject> mo, int mapObjectId);
      static RowSet* loadInventory(sqlite3 *db, int inventoryId);
      static RowSet* loadHardpoints(sqlite3 *db, int smoId);
      static RowSet* loadInteractionpoints(sqlite3 *db, int smoId);
      static RowSet* loadInteractions(sqlite3 *db, int smoId, int interactionType);
      static RowSet* loadNonPlayerCharacterPath(sqlite3 *db, int npcId);

      static sqlite3* db;
   public:
      static bool build(sqlite3 *db, int boxX, int boxY);
};

#endif //MAP_OBJECT_FACTORY_H
