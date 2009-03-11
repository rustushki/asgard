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

#include "Hardpoint.h"
#include "RowSet.h"
 
class MapObjectFactory
{
   private:
      static void createTile(char **columnValue);
      static void createContainer(char **columnValue);
      static void createNonPlayerCharacter(char **columnValue);
      static void createStaticMapObject(char **columnValue);
      static Hardpoint* createHardpoint(RowSet* rs, int row);
      static Coordinate* createNonPlayerCharacterPathPoint(RowSet* rs, int row);
      
   public:
      static int processRow(void *mapObjectType, int columnCount, char **columnValue, char **columnName); 
      
};

#endif //MAP_OBJECT_FACTORY_H

