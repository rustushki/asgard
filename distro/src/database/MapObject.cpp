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
   for (unsigned int x = 0; x < this->interactions.size(); x++) {
      delete this->interactions[x];
   }
   for (unsigned int x = 0; x < this->interactions.size(); x++) {
      delete this->interactionpoints[x];
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
      return d->getHeight();
   } else {
      LOG(FATAL) << "Drawable " << this->getDrawableName() << "didn't exist";
   }

   return 0;
}

/* -----------------------------------------------------------------------------
 * getMiddle - Return the Y of the horizontal line dividing the MapObject in
 * half.
 */
int MapObject::getMiddle() const {
	Coordinate topLc = this->getLeftCorner();
	return topLc.getY() + this->getHeight()/2;
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

/* -----------------------------------------------------------------------------
 * getFoot - Return the world coordinate of the center of the bottom of the 
 *           MapObject.
 */
Coordinate MapObject::getFoot() const
{
   Coordinate topLc = this->getLeftCorner();
   Coordinate foot(topLc.getX()+this->getWidth()/2, this->getBottom());
   return foot;
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

bool MapObject::conflict(Coordinate c) {
   std::vector<Hardpoint*>::const_iterator hpItr;
   bool isConflict = false;
   for(hpItr = hardpoints.begin(); hpItr < hardpoints.end(); hpItr++)
   {
      // Does Coordinate c conflict with MapObject's Hardpoint?
      if((*hpItr)->conflict(c,this->leftCorner))
      {
         // TO DO: Implement algorithm for maneuvering around Hardpoint
         isConflict = true;
         break;
      }
   }

   return isConflict;
}

/* ------------------------------------------------------------------------------
 * intersects - Return true if this MapObject intersects with the provided
 * MapObject.
 *
 * Please note that this is not a hard point collision.  This merely means that
 * the two MapObjects' Drawables are occupying some of the same x/y space.
 */
bool MapObject::intersects(MapObject* that) {
	return !(
		   this->getBottom() < that->getTop()
		|| this->getLeft()   > that->getRight()
		|| this->getRight()  < that->getLeft()
		|| this->getTop()    > that->getBottom()
	);
}

void MapObject::addInteractionpoint(Interactionpoint *interactionpoint)
{
   this->interactionpoints.push_back(interactionpoint);
}

void MapObject::interacts(MapObject *accepter, bool wasMouseClicked)
{
   std::vector<Interactionpoint*>::const_iterator ipItr;
   std::vector<Interaction*>::const_iterator iItr;

   for(ipItr = accepter->interactionpoints.begin(); ipItr < accepter->interactionpoints.end(); ipItr++)
   {
      // Do not allow Interactions when mouse was not clicked on an Interactionpoint
      // requiring a click (e.g. Interactionpoint for a treasure chest)
      if(((*ipItr)->getRequiresMouseClick() == true) && (wasMouseClicked == false))
         continue;

      // Is initiator MapObject's foot within accepter MapObject's Interactionpoint(s)?
      if((*ipItr)->conflict(accepter->leftCorner,this->getFoot()))
      {
         // Handle Interactions
         for(iItr = accepter->interactions.begin(); iItr < accepter->interactions.end(); iItr++)
         {
            switch ((*iItr)->getType())
            {
               case INTERACTION_TYPE_ANIMATION:
                  accepter->drawable->swapAnimation(((AnimationInteraction *)(*iItr))->getAnimationName());
                  break;
               case INTERACTION_TYPE_ITEM:
                  accepter->inv->transferItemToInventory(((ItemInteraction *)(*iItr))->getItemName(),this->inv);
                  break;
               case INTERACTION_TYPE_DIALOG:
                  accepter->dialog->setText(((DialogInteraction *)(*iItr))->getQuote());
                  break;
               default:
                  std::cout<<"ERROR: Undefined Interaction"<<std::endl;
            }
            // Remove Interaction if it is only handled once
            if((*iItr)->getIsHandledOnce()) 
               interactions.erase(interactions.begin() + (*iItr)->getPriority());
         }
         break; // This MapObject's foot only needs to be within one Interactionpoint
      }
   }
}

void MapObject::addInteraction(Interaction *interaction)
{
   int priority = interaction->getPriority();

   // Ensure that enough space is allocated to the vector to accommodate 
   // insertion of interaction at position interactions[priority]
   if(priority >= (int)interactions.capacity())
      interactions.resize(priority+1);

   interactions[priority] = interaction;
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
      LOG(ERROR) << angle;
      if(angle <= 22)
         angle = 90;
      else if((angle >= 23) && (angle <= 67))
         angle = 135;
      else if(angle >= 68)
         angle = 180;
   }
 
   return angle;
}

/* ------------------------------------------------------------------------------
 * move - Move the MapObject to the provided X and Y.
 */
void MapObject::move(int newX, int newY) {

   // Set state to 'moving'
   this->state = MAP_OBJECT_STATE_MOVING;

   // Set new LeftCorner
   Coordinate newLC(newX,newY);
   this->setLeftCorner(newLC);

   // Set state to 'idle'
   this->state = MAP_OBJECT_STATE_IDLE;
}

/* ------------------------------------------------------------------------------
 * move - Move the MapObject to the Coordinate.
 */
void MapObject::move(Coordinate newLoc) {
   move(newLoc.getX(), newLoc.getY());
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

void MapObject::setDrawable(Drawable *d) {
   this->drawable = d;
}

Drawable* MapObject::getDrawable() const {
   return this->drawable;
}
