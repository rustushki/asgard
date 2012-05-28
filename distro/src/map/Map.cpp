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

#include "Map.h"

Map* Map::instance = NULL;

Map::Map() {
   LOG(INFO) << "Map starting ...";


   //
   // BEGIN -- CODE THAT DOES NOT BELONG HERE

      // CharacterMapObjects don't belong in the database, but if not there,
      // then where?  I would argue in a Binary Packed Save file, but we don't
      // have such a thing just yet.  Let's temporarily build our CMO and its
      // drawable at Map instantiation.

      Drawable* d = new Drawable("NotMatch");

      Animation* a1 = new Animation("NotMatchStandingEast.png", 59, 100, 1, 1, 1);
      Animation* a2 = new Animation("NotMatchStandingWest.png", 59, 100, 1, 1, 1);
      Animation* a3 = new Animation("NotMatchWalkingEast.png", 59, 100, 7, 1, 7);
      Animation* a4 = new Animation("NotMatchWalkingWest.png", 59, 100, 7, 1, 7);
      
      d->addAnimation(a1, "NotMatchStandingEast");
      d->addAnimation(a2, "NotMatchStandingWest");
      d->addAnimation(a3, "NotMatchWalkingEast");
      d->addAnimation(a4, "NotMatchWalkingWest");

      CharacterMapObject* cmo = new CharacterMapObject(d->getInstanceName());

      // These are mostly irrelevant at the moment.
      // They become more important when hard points are used.
      cmo->setStep(1);
      cmo->setState(MAP_OBJECT_STATE_IDLE);

      // x = 300, y = 300 puts this CMO in BB (0, 0)
      cmo->setLeftCorner(Coordinate(300,400));

      this->installMapObject(cmo, d);

      // Useful for testing animations ...
      //d->swapAnimation("NotMatchWalkingEast");

   // END -- CODE THAT DOES NOT BELONG HERE
   //



   // Set the Map Pan Threshold to 10%.
   this->threshold = 0.10;

}

Map::~Map() {

}

Map* Map::getInstance() {
   if (instance == NULL)
      instance = new Map();

   return instance;
}

void Map::setFocusPoint(int x, int y) {

   LOG(INFO) << "Setting Map Focus Point = " << x << ", " << y;	

   // TODO: Maximum Map dimensions is currently out of scope.

   Coordinate newFocus(x, y);
   Coordinate offset = this->focus - newFocus;

   // Move the Existing Drawables.
   this->moveDrawables(offset);
   this->adjustDisplay();

   // Change Focus and Load/Unload Bounding Boxes.
   this->focus = newFocus;
   this->loadBoundingBoxes();
   this->unloadBoundingBoxes();
}

void Map::panFocusPoint(int x, int y) {

    // This is the focus point before the Map Pan started.
    Coordinate startFocusPoint = this->focus;

    // The point to which we would like to pan the focus point.
    Coordinate finalFocusPoint(x, y);

    // The difference between the two points.
    Coordinate offset = startFocusPoint - finalFocusPoint;

    // The total amount of time the panning should take (in milliseconds).
    // This could be parameterized later.
    int duration = 700;

    // The number of times per the duration of time that we want to set the
    // intermediate focus point.  This could be parameterized later.
    int step = 15;

    // Amount of time to pause between each intermediate setting of the focus point.
    int wait = duration/step;


    Coordinate stepOffset(offset.getX()/step, offset.getY()/step);

    for (int stepCv = 0; stepCv < step; stepCv++) {
        
        // Determine the next temporary focus point.
        Coordinate tempFocusPoint = this->focus - stepOffset;

        // Set to the next temporary focus point.
        this->setFocusPoint(tempFocusPoint.getX(), tempFocusPoint.getY());

        // Wait.
        SDL_Delay(wait);
    }

    // This method must ensure that the final focus point is set correctly.  Do
    // this last step in case of any rounding errors in integer math.
    if (this->focus != finalFocusPoint) {
        this->setFocusPoint(finalFocusPoint.getX(), finalFocusPoint.getY());
    }

}

void Map::moveDrawables(Coordinate offset) {

   std::vector<std::string>* drawableNames = new std::vector<std::string>();

   std::vector<MapObject*>::iterator moIter;
   for (moIter = this->mapObjectContainer.begin(); moIter != this->mapObjectContainer.end(); moIter++) {
      drawableNames->push_back((*moIter)->getDrawableName());
   }

   GraphicsEngine::getInstance()->translateDrawablesByOffset(drawableNames, offset.getX(), offset.getY());
}

void Map::loadBoundingBoxes() {
   Coordinate tl = this->getTopLeftOfRegion();
   for (int x = 0; x < Map::BOUNDING_BOX_MEM; x++) {
      for (int y = 0; y < Map::BOUNDING_BOX_MEM; y++) {
         Coordinate bb(
              tl.getX() + x * Map::BOUNDING_BOX_SIZE
            , tl.getY() + y * Map::BOUNDING_BOX_SIZE
         );
         this->loadBoundingBox(bb);
      }
   }
}

void Map::unloadBoundingBoxes() {
   std::vector<Coordinate>::iterator bbIter;
   for (bbIter = this->boundingBoxContainer.begin(); bbIter != this->boundingBoxContainer.end(); bbIter++) {
      if (!this->isBoundingBoxInScope(*bbIter)) {
         this->boundingBoxContainer.erase(bbIter);
      }
   }
   this->unloadMapObjects();
}

void Map::loadBoundingBox(Coordinate bb) {
   if (this->isValidBoundingBox(bb)) {

      if (!this->isBoundingBoxLoaded(bb)) {
         LOG(INFO) << "Loading Bounding Box (" << bb.getX() << "," << bb.getY() << ")";

         Database* db = Database::getInstance();
         if (db->loadBoundingBox(bb.getX(), bb.getY())) {
            this->boundingBoxContainer.push_back(bb);
         }
      } else {
         LOG(INFO) << "Bounding Box (" << bb.getX() << "," << bb.getY() << ") already loaded.";
      }
   } else {
      LOG(INFO) << "Invalid Bounding Box (" << bb.getX() << "," << bb.getY() << ")";
   }
}

bool Map::isBoundingBoxLoaded(Coordinate bb) {
   bool alreadyLoaded = false;
   std::vector<Coordinate>::iterator bbIter;
   for (bbIter = this->boundingBoxContainer.begin(); bbIter != this->boundingBoxContainer.end(); bbIter++) {

      if ((*bbIter) == bb) {
         alreadyLoaded = true;
         break;
      }
   }

   return alreadyLoaded;
}

/** Restack MapObjects
 *
 * Given two MapObjects A and B, put A on top of B if A's bottom is lower than
 * B's middle.  Otherwise, stack A beneath B.
 * 
 */
void Map::restack(MapObject* a, MapObject* b) const {
   // Need the Drawable Names so that we may perform operations on the
   // GraphicsEngine.
   std::string aName = a->getDrawableName();
   std::string bName = b->getDrawableName();

   // Grab an instance of the GraphicsEngine.
   GraphicsEngine* ge = GraphicsEngine::getInstance();

   // Get the Layer of the Drawables for these MapObjects.
   // TODO: We need a stricter relationship between the Map and any layers that
   // it governs.
   Layer* lA = ge->getLayerOfDrawable(aName);
   Layer* lB = ge->getLayerOfDrawable(aName);
   assert(lA == lB);

   if (a->getBottom() < b->getMiddle()) {
      // Put A on Top.
      lA->stackAonB(aName, bName);
   } else {
      // Put B on Top.
      lA->stackAonB(bName, aName);
   }
}

bool Map::isValidBoundingBox(Coordinate bb) {
   if (bb.getX() % Map::BOUNDING_BOX_SIZE != 0) {
      return false;
   }

   if (bb.getY() % Map::BOUNDING_BOX_SIZE != 0) {
      return false;
   }

   return true;
}

/** Unload MapObjects from Map.
 *
 * Any MapObjects that have fallen out of the Region of Relevance must be
 * removed from the Map.  Consequently, any Drawables associated with these
 * MapObjects must also be removed from the Graphics Engine.  Send an
 * UnloadDrawable message to Graphics Engine to accomplish this.
 * 
 * @return
 */
void Map::unloadMapObjects() {
   // Grab a reference to the container for MapObjects for shorter code.
   std::vector<MapObject*>* map = &(this->mapObjectContainer);

   // Iterate through each MapObject loaded on the Map ...
   std::vector<MapObject*>::iterator moIter = map->begin();
   while (moIter != map->end()) {

      MapObject* mo = *moIter;

      // Is the MapObject in the Region of Relevance?
      if (!this->isMapObjectInScope(mo)) {
         LOG(INFO) << "MapObject not in scope.";

         // Unload the Drawable from the Graphics Engine.
         GraphicsEngine::getInstance()->unloadDrawable(mo->getDrawableName());

         // Remove the MapObject from the Map; freeing its memory.
         moIter = map->erase(moIter);
      } else {
         moIter++;
      }
   }

}

bool Map::isBoundingBoxInScope(Coordinate bb) {
   Coordinate tl = this->getTopLeftOfRegion();
   for (int x = 0; x < Map::BOUNDING_BOX_MEM; x++) {
      for (int y = 0; y < Map::BOUNDING_BOX_MEM; y++) {

         Coordinate thisBB(
              tl.getX() + x * Map::BOUNDING_BOX_SIZE
            , tl.getY() + y * Map::BOUNDING_BOX_SIZE
         );

         if (bb == thisBB) {
            return true;
         }
      }
   }

   return false;
}

bool Map::isMapObjectInScope(MapObject* mo) {

   // Top Left Corner of MapObject in Question.
   Coordinate tl = mo->getLeftCorner();

   Coordinate rr = this->getTopLeftOfRegion();

   // Determine Dimensions of Region of Relevance
   int rrSize = Map::BOUNDING_BOX_SIZE*Map::BOUNDING_BOX_MEM;

   // If the MapObject is x dimensionally out of bounds...
   if (tl.getX() > rr.getX() + rrSize || tl.getX() < rr.getX()) {
      // Out of Scope.
      return false;
   }

   // If the MapObject is y dimensionally out of bounds...
   if (tl.getY() > rr.getY() + rrSize || tl.getY() < rr.getY()) {
      // Out of Scope.
      return false;
   }

   // Otherwise, in Scope.
   return true;
}

Coordinate Map::getFocusBoundingBox() {
   // The current focus of the Map.
   Coordinate f = this->focus;

   // Determine the Bounding Box which contains the focus. (i.e. the Middle)
   int bX = f.getX() - (f.getX() % Map::BOUNDING_BOX_SIZE);
   int bY = f.getY() - (f.getY() % Map::BOUNDING_BOX_SIZE);

   return Coordinate(bX, bY);
}

Coordinate Map::getTopLeftOfRegion() {
   Coordinate bb = this->getFocusBoundingBox();

   // Given the Middle determine the Top Left of the Region of Relevance.
   int middle = Map::BOUNDING_BOX_MEM / 2;
   int tlrrX = bb.getX() - middle * Map::BOUNDING_BOX_SIZE;
   int tlrrY = bb.getY() - middle * Map::BOUNDING_BOX_SIZE;

   return Coordinate(tlrrX, tlrrY);
}

void Map::adjustDisplay() {

   Coordinate offset(Screen::WIDTH/2, Screen::HEIGHT/2);
   this->display = this->focus - offset;

   int x = this->display.getX();
   int y = this->display.getY();
   LOG(INFO) << "Set Map Display Point = " << x << ", " << y;	
}

void Map::installMapObject(MapObject* mo, Drawable* d) {
   
   // Install the MapObject.
   this->mapObjectContainer.push_back(mo);

   Coordinate drawableCoord = this->convertWorldToScreen(mo->getLeftCorner());
   int x = drawableCoord.getX();
   int y = drawableCoord.getY();
   d->setX(x);
   d->setY(y);

   GraphicsEngine::getInstance()->displayDrawable(d, "stageLayer", x, y);
}

void Map::handle(SDL_Event event) {
   switch (event.type) {
      case SDL_KEYDOWN:
         std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
         break;
      case SDL_MOUSEBUTTONDOWN:

         LOG(INFO) << "Map Click: " << event.button.x << ", " << event.button.y;

         {

            // Translate the SDL_MOUSEBUTTONDOWN into Asgard's move CMO event.
            // Use CANCEL event concurrency policy to prevent multiple user
            // clicks from creating erratic movement.
            Coordinate* c = new Coordinate(event.button.x, event.button.y);
            this->fireEvent(ASGARDEVENT_MOVECMO, c, CONCURRENCY_POLICY_CANCEL);

         }


         break;
      case SDL_USEREVENT:

         if (event.user.code == ASGARDEVENT_MAPPAN) {

            Coordinate *panHereCoord = (Coordinate*) event.user.data1;

            this->panFocusPoint(panHereCoord->getX(), panHereCoord->getY());

         } else if (event.user.code == ASGARDEVENT_MOVECMO) {

            // Grab the CMO.
            CharacterMapObject* cmo = this->getCharacterMapObject();

            // Get the x/y of the Move CMO Event.
            Coordinate* c = (Coordinate*)event.user.data1;

            // Convert the provided screen coordinate into a world coordinate.
            Coordinate newCMOWorldCoordinate = convertScreenToWorld(*c);

            // Offset the New World Coordinate by the distance between the Top
            // Left Corner of the CMO and it's foot.  That way, the CMO will
            // arrive at the provided coordinate "on it's foot"
            newCMOWorldCoordinate -= cmo->getFoot() - cmo->getLeftCorner();

            // x & y are the World Coordinate at which the CMO should end up.
            int x = newCMOWorldCoordinate.getX();
            int y = newCMOWorldCoordinate.getY();

            int angle, step, draw_oldX, draw_oldY, draw_newX, draw_newY;
            std::string drawableName, walkingAnimationName, standingAnimationName;
            Drawable *d;

            // Get Drawable for CharacterMapObject
            drawableName = cmo->getDrawableName();
            d = GraphicsEngine::getInstance()->getDrawableByName(drawableName);
            
            // Get Drawable's common name (not with unique ID)
            drawableName = d->getName();

            // Convert the Drawable's X & Y into a World Coordinate.
            Coordinate drawableOld(d->getX(), d->getY());
            drawableOld = convertScreenToWorld(drawableOld);
            draw_oldX = drawableOld.getX();
            draw_oldY = drawableOld.getY();

            // Compute MapObject's angle of movement
            angle = cmo->computeAngleOfMovement(x, y, draw_oldX, draw_oldY);
            switch (angle)
            {
               case 0:
                  walkingAnimationName = drawableName + "WalkingEast";
                  standingAnimationName = drawableName + "StandingEast";
                  break;
               case 45:
                  //animationName = drawableName + "NorthEast";
                  walkingAnimationName = drawableName + "WalkingEast";
                  standingAnimationName = drawableName + "StandingEast";
                  break;
               case 90:
                  //animationName = drawableName + "North";
                  walkingAnimationName = drawableName + "WalkingEast";
                  standingAnimationName = drawableName + "StandingEast";
                  break;
               case 135:
                  //animationName = drawableName + "NorthWest";
                  walkingAnimationName = drawableName + "WalkingWest";
                  standingAnimationName = drawableName + "StandingWest";
                  break;
               case 180:
                  walkingAnimationName = drawableName + "WalkingWest";
                  standingAnimationName = drawableName + "StandingWest";
                  break;
               case 225:
                  //animationName = drawableName + "SouthWest";
                  walkingAnimationName = drawableName + "WalkingWest";
                  standingAnimationName = drawableName + "StandingWest";
                  break;
               case 270:
                  //animationName = drawableName + "South";
                  walkingAnimationName = drawableName + "WalkingWest";
                  standingAnimationName = drawableName + "StandingWest";
                  break;
               case 315:
                  //animationName = drawableName + "SouthEast";
                  //animationName = drawableName + "WalkingWest";
                  walkingAnimationName = drawableName + "WalkingEast";
                  standingAnimationName = drawableName + "StandingEast";
                  break;
               default:
                  break;
            }

            if(d->swapAnimation(walkingAnimationName))
               LOG(INFO) << "Animation " << walkingAnimationName << " swapped into Drawable " << drawableName;

            /* Get step for MapObject */
            step = cmo->getStep();

            /* Move Drawable and MapObject by step */
            while((draw_oldX != x) || (draw_oldY != y))
            {
               /*DEBUG
               break; END-DEBUG */
               /* Determine new x location */
               if(draw_oldX > x)
               {
                  if((draw_oldX - step) < x)
                     draw_newX = x;
                  else
                     draw_newX = draw_oldX - step;
               }
               else if(draw_oldX < x)
               {
                  if((draw_oldX + step) > x)
                     draw_newX = x;
                  else
                     draw_newX = draw_oldX + step;
               }
               else
                  draw_newX = draw_oldX;

               /* Determine new y location */
               if(draw_oldY > y)
               {
                  if((draw_oldY - step) < y)
                     draw_newY = y;
                  else
                     draw_newY = draw_oldY - step;
               }
               else if(draw_oldY < y)
               {
                  if((draw_oldY + step) > y)
                     draw_newY = y;
                  else
                     draw_newY = draw_oldY + step;
               }
               else
                  draw_newY = draw_oldY;
                     
               /* Move MapObject with respect to World Coordinate */
               Coordinate newLoc(draw_newX, draw_newY);
               cmo->move(newLoc);

               /* Move Drawable with respect to Screen Coordinate */
               newLoc = convertWorldToScreen(newLoc);
               d->move(newLoc.getX(),newLoc.getY());

               /* Set current location */
               draw_oldX = draw_newX;
               draw_oldY = draw_newY;

               // Check if the CMO is over the Map Pan threshold.  Fire Map Pan
               // event if so.
               this->checkOverMapPanThreshold();

               SDL_Delay(10);
            }

            /* Swap in Animation for standing */
            if(d->swapAnimation(standingAnimationName))
               LOG(INFO) << "Animation " << standingAnimationName << " swapped into Drawable " << drawableName;
         }

         break;
      
      default:
         break;
   }
}

/* -----------------------------------------------------------------------------
 * convertScreenToWorld - Given a screen coordinate, convert it into a World
 * Coordinate--which is a point on the Map.
 */
Coordinate Map::convertScreenToWorld(Coordinate s) const {

   // Add the World Coordinate of the current location of the top left corner
   // of the Screen to the provided screen coordinate and return the result.
   return (this->display + s);

}

/* -----------------------------------------------------------------------------
 * convertWorldToScreen - Given a world coordinate, convert it into a Screen
 * coordinate.  Screen coordinates which are visible to the user are greater
 * than (0,0), but less than the Height and Width of the screen.
 */
Coordinate Map::convertWorldToScreen(Coordinate w) const {
   
    // The offset between the provided world coordinate and the current display
    // coordinate is equivalent to its Screen Coordinate.
    return (w - this->display);

}

/* -----------------------------------------------------------------------------
 * checkOverMapPanThreshold - Check if the CharacterMapObject is inside any of
 * the margins of the screen.  The margins are determined by the threshold
 * member of map.
 *
 * If the CharacterMapObject is within the threshold, fire off a Map Pan Event.
 */
void Map::checkOverMapPanThreshold() const {

   // Find the CharacterMapObject.  As of 0.3.8, there's only 1.
   CharacterMapObject* cmo = this->getCharacterMapObject();

   // Compute top, bottom, right and left margins of the screen.
   int top    = Screen::HEIGHT * threshold;
   int bottom = Screen::HEIGHT - top;
   int left   = Screen::WIDTH  * threshold;
   int right  = Screen::WIDTH  - left;

   // Convert those margins into their world equivalents.
   top    += this->display.getY();
   bottom += this->display.getY();
   left   += this->display.getX();
   right  += this->display.getX();

   // Check if the CMO has exceeded the Top, Bottom, Left and Right Margins.
   if (    cmo->getTop()  < top  || cmo->getBottom() > bottom
        || cmo->getLeft() < left || cmo->getRight()  > right) {

      // If any is exceeded, fire a Map Pan Event.
      LOG(INFO) << "firing map pan event";

      // The Coordinate of the CMO is the parameter of the Map Pan Event.
      Coordinate tLc = cmo->getLeftCorner();
      Coordinate* panHereCoord = new Coordinate(tLc.getX(), tLc.getY());
      this->fireEvent(ASGARDEVENT_MAPPAN, (void*)panHereCoord, CONCURRENCY_POLICY_CANCEL);

   }

}

/* -----------------------------------------------------------------------------
 * getCharacterMapObject - Get the CharacterMapObject.  This method should go
 * away in later releases when we have more complex entities like Parties and
 * PlayableCharacters.
 *
 * Return NULL if none found.
 */
CharacterMapObject* Map::getCharacterMapObject() const {

   CharacterMapObject* cmo = NULL;

   // Iterate over MapObjects on the Map.  Find the one which is the
   // CharacterMapObject and move it to the provided x/y.
   std::vector<MapObject*>::const_iterator itr;
   for (itr = mapObjectContainer.begin(); itr < mapObjectContainer.end(); itr++) {

      // In Asgard 0.3.8, there will be only one CharacterMapObject.
      if(dynamic_cast<CharacterMapObject*>(*itr)) {
         cmo = dynamic_cast<CharacterMapObject*>(*itr);
         break;
      }
   }

   return cmo;
}
