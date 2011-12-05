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

#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "externals.h"
#include "Coordinate.h"

#define MAP_OBJECT_HEIGHT_DEFAULT   10
#define MAP_OBJECT_WIDTH_DEFAULT    10

using std::list;

class MapObject
{
   public:
      MapObject(std::string drawableName);
      virtual ~MapObject();
      
      void setLeftCorner(const Coordinate& leftCorner);
      Coordinate getLeftCorner();
      void setHeight(int height);
      void setWidth(int width);

      std::string getDrawableName();
      
      void addBoundingBox(int boundingBox);
      
   private:
      Coordinate leftCorner;
      list<int> boundingBoxes;
      int height,width;
      std::string drawableName;
};
#endif //MAP_OBJECT_H