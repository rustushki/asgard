/*****************************************************************************
 * Copyright (c) 2012 Russ Adams, Sean Eubanks, Asgard Contributors
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

MapObject::MapObject(std::string drawableName)
{
   this->height = MAP_OBJECT_HEIGHT_DEFAULT;
   this->width = MAP_OBJECT_WIDTH_DEFAULT;
   this->drawableName = drawableName;
   this->step = 1;
   this->setState(MAP_OBJECT_STATE_IDLE);
}

MapObject::~MapObject() {
   for (unsigned int x = 0; x < this->hardpoints.size(); x++) {
      delete this->hardpoints[x];
   }
}

void MapObject::setLeftCorner(const Coordinate& leftCorner)
{
   this->leftCorner = leftCorner;
}

Coordinate MapObject::getLeftCorner() {
   return this->leftCorner;
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

std::string MapObject::getDrawableName()
{
	return this->drawableName;
}

void MapObject::addHardpoint(Hardpoint *hardpoint) {
   this->hardpoints.push_back(hardpoint);
}

bool MapObject::collide(MapObject*) {
   return false;
}

/***********************************************************
 * move - Given a newX and a newY, do several things: 
 *
 * 1. Update MobileMapObject state to 'moving'.  'state' is an enumerated type
 *    member of MobileMapObject.  It may be 'idle' or 'moving'.
 * 2. Compute the angle of movement using Pythagorean Theorem.
 * 3. Use the angle of movement to determine the animation to swap in for the
 *    Drawable. 
 * 4. Instruct the associated drawable to move Step by Step across the map in a
 *    loop.  Step is a member of MobileMapObject.  Step is an integral distance.
 * 5. Sleep a certain duration between each movement of the Drawable so that
 *    the user has time to see the Drawable move.
 * 6. Update the MapObject's World Coordinate each iteration of the loop.
 *
 * Points #4-6 are OK because 'move()' must be run in an event thread (thus it
 * won't block the main thread of execution).
 */
void MapObject::move(int newX, int newY) {

   // TODO: we should probably enforce that this run inside a special thread,
   // but it's unclear how to discern threads right now.  feel free to leave
   // this here as a cautionary tale to the next programmer.
   
   // TODO: implement the above 6 points.

   // Computational Handwaving.
}

void MapObject::setState(MapObjectState state) {
   this->state = state;
}
