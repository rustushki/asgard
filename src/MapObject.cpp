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

#include "MapObject.h"

MapObject::MapObject()
{
   this->height = MAP_OBJECT_HEIGHT_DEFAULT;
   this->width = MAP_OBJECT_WIDTH_DEFAULT;
}

MapObject::MapObject(const Coordinate& leftCorner,int height,int width)
{
   this->leftCorner = leftCorner;
   this->height = height;
   this->width = width;
}

void MapObject::setLeftCorner(const Coordinate& leftCorner)
{
   this->leftCorner = leftCorner;
}

void MapObject::setHeight(int height)
{
   assert(height != 0);
   
   this->height = height;
}

void MapObject::setWidth(int width)
{
   assert(width != 0);
   
   this->width = width;
}
      
void MapObject::addBoundingBox(int boundingBox)
{
   this->boundingBoxes.push_back(boundingBox);
}
