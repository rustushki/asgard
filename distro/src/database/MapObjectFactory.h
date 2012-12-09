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
#include "Hardpoint.h"
#include "Interaction.h"
#include "RowSet.h"
#include "Tile.h"
#include "WaterTile.h"
#include "GrassTile.h"
#include "DesertTile.h"
#include "Container.h"
#include "NonPlayerCharacter.h"
#include "DatabaseColumnMap.h"
#include "CircHardpoint.h"
#include "RectHardpoint.h"
#include "QueryGenerator.h"
#include "Drawable.h"
#include "DrawableFactory.h"

class MapObjectFactory
{
   private:
      static void createTile(sqlite3_stmt *stmt);
      static void createContainer(sqlite3 *db, sqlite3_stmt *stmt);
      static void createNonPlayerCharacter(sqlite3 *db, sqlite3_stmt *stmt);
      static void createMapObject(sqlite3 *db, sqlite3_stmt *stmt);
      static Hardpoint* createHardpoint(RowSet* rs, int row);
      static Interaction* createInteraction(RowSet* rs, int row);
      static Coordinate* createNonPlayerCharacterPathPoint(RowSet* rs, int row);
      static RowSet* loadHardpoints(sqlite3 *db, int smoId);
      static RowSet* loadInteractions(sqlite3 *db, int smoId);
      static RowSet* loadNonPlayerCharacterPath(sqlite3 *db, int npcId);

      static sqlite3* db;
   public:
      static bool build(sqlite3 *db, int boxX, int boxY);
};

#endif //MAP_OBJECT_FACTORY_H
