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
#include "GraphicsEngine.h"
#include "Drawable.h"

MapObject::MapObject(std::string drawableName)
{
   this->drawableName = drawableName;
   this->step = 1;
   this->state = MAP_OBJECT_STATE_IDLE;
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

Coordinate MapObject::getLeftCorner() const {
   return this->leftCorner;
}

/* -----------------------------------------------------------------------------
 * getWidth - Return the width in pixels of the MapObject.  Internally, this
 * maps to the width of the associated drawable.  Fail miserably when
 * associated drawable doesn't exist.
 */
uint MapObject::getWidth() const {

   GraphicsEngine* ge = GraphicsEngine::getInstance();

   Drawable* d = ge->getDrawableByName(this->getDrawableName());

   if (d != NULL) {
      return d->getWidth();
   } else {
      LOG(FATAL) << "Drawable " << this->getDrawableName() << "didn't exist";
   }

   return 0;
}

/* -----------------------------------------------------------------------------
 * getHeight - Return the height in pixels of the MapObject.  Internally, this
 * maps to the height of the associated drawable.  Fail miserably when
 * associated drawable doesn't exist.
 */
uint MapObject::getHeight() const {

   GraphicsEngine* ge = GraphicsEngine::getInstance();

   Drawable* d = ge->getDrawableByName(this->getDrawableName());

   if (d != NULL) {
      return d->getWidth();
   } else {
      LOG(FATAL) << "Drawable " << this->getDrawableName() << "didn't exist";
   }

   return 0;
}


/* -----------------------------------------------------------------------------
 * getBottom - Return the Y of the bottom edge of the MapObject.
 */
int MapObject::getBottom() const {
	Coordinate topLc = this->getLeftCorner();
	return topLc.getY() + this->getHeight();
}

/* -----------------------------------------------------------------------------
 * getTop - Return the Y of the top edge of the MapObject.
 */
int MapObject::getTop() const {
	Coordinate topLc = this->getLeftCorner();
	return topLc.getY();

}

/* -----------------------------------------------------------------------------
 * getLeft - Return the X of the left edge of the MapObject.
 */
int MapObject::getLeft() const {
	Coordinate topLc = this->getLeftCorner();
	return topLc.getX();
}

/* -----------------------------------------------------------------------------
 * getRight - Return the X of the right edge of the MapObject.
 */
int MapObject::getRight() const {
	Coordinate topLc = this->getLeftCorner();
	return topLc.getX() + this->getWidth();
}

void MapObject::addBoundingBox(int boundingBox)
{
   this->boundingBoxes.push_back(boundingBox);
}

/* -----------------------------------------------------------------------------
 * getDrawableName - Return the instance name of the associated drawable.
 */
std::string MapObject::getDrawableName() const
{
	return this->drawableName;
}

void MapObject::addHardpoint(Hardpoint *hardpoint) {
   this->hardpoints.push_back(hardpoint);
}

bool MapObject::collide(MapObject*) {
   return false;
}

int MapObject::computeAngleOfMovement(int newX, int newY, int oldX, int oldY)
{
   int angle = 0;

   if(newY == oldY)
      if(newX > oldX)
      {
         angle = 0; // Move east
      }
      else
         angle = 180; // Move west
   else if(newX == oldX)
      if(newY > oldY)
         angle = 270; // Move south
      else
         angle = 90; // Move north
   // Move southwest
   else if((newX < oldX) && (newY > oldY))
   {
      int oppSide, adjSide;
      oppSide = fabs(newY-oldY);
      adjSide = fabs(newX-oldX);
      angle = atan(oppSide/adjSide)*(double)((float)180/PI);
      if(angle <= 22)
         angle = 180;
      else if((angle >= 23) && (angle <= 67))
         angle = 225;
      else if(angle >= 68)
         angle = 270;
   }
   // Move southeast
   else if((newX > oldX) && (newY > oldY))
   {
      int oppSide, adjSide;
      oppSide = fabs(newX-oldX);
      adjSide = fabs(newY-oldY);
      angle = atan(oppSide/adjSide)*(double)((float)180/PI);
      if(angle <= 22)
         angle = 270;
      else if((angle >= 23) && (angle <= 67))
         angle = 315;
      else if(angle >= 68)
         angle = 0;
   }
   // Move northeast
   else if((newX > oldX) && (newY < oldY))
   {
      int oppSide, adjSide;
      oppSide = fabs(newY-oldY);
      adjSide = fabs(newX-oldX);
      angle = atan(oppSide/adjSide)*(double)((float)180/PI);
      if(angle <= 22)
         angle = 0;
      else if((angle >= 23) && (angle <= 67))
         angle = 45;
      else if(angle >= 68)
         angle = 90;
   }
   // Move northwest
   else if((newX < oldX) && (newY < oldY))
   {
      int oppSide, adjSide;
      oppSide = fabs(newX-oldX);
      adjSide = fabs(newY-oldY);
      angle = atan(oppSide/adjSide)*(double)((float)180/PI);
      if(angle <= 22)
         angle = 90;
      else if((angle >= 23) && (angle <= 67))
         angle = 135;
      else if(angle >= 68)
         angle = 180;
   }
 
   return angle;
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
 *    loop.  Step is a member of MapObject.  Step is an integral distance.
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

   // Set state to 'moving'
   this->state = MAP_OBJECT_STATE_MOVING;

   // Set new LeftCorner
   Coordinate *newLC = new Coordinate(newX,newY);
   this->setLeftCorner(*newLC);

   // Set state to 'idle'
   this->state = MAP_OBJECT_STATE_IDLE;
}

void MapObject::setState(MapObjectState state) {
   this->state = state;
}

MapObjectState MapObject::getState() {
   return this->state;
}

void MapObject::setStep(int step) {
   this->step = step;
}

int MapObject::getStep() {
   return this->step;
}
