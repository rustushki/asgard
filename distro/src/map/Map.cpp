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
#include "GuiFactory.h"

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

      CharacterMapObject* cmo = new CharacterMapObject(d);

      // These are mostly irrelevant at the moment.
      // They become more important when hard points are used.
      cmo->setStep(1);
      cmo->setState(MAP_OBJECT_STATE_IDLE);

      // x = 300, y = 300 puts this CMO in BB (0, 0)
      cmo->setLeftCorner(Coordinate<MapPoint>(300,400));

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

   Coordinate<MapPoint> newFocus(x, y);
   Coordinate<MapPoint> offset = this->focus - newFocus;

   // Move the Existing Drawables.
   this->moveDrawables(offset);

   // Change Focus and Load/Unload Bounding Boxes.
   this->focus = newFocus;

   // Order is important here ... the display should only be adjusted AFTER
   // changing the location of the map focus.
   this->adjustDisplay();

   this->loadBoundingBoxes();
   this->unloadBoundingBoxes();
}

void Map::panFocusPoint(int x, int y) {

    // This is the focus point before the Map Pan started.
    Coordinate<MapPoint> startFocusPoint = this->focus;

    // The point to which we would like to pan the focus point.
    Coordinate<MapPoint> finalFocusPoint(x, y);

    // The difference between the two points.
    Coordinate<MapPoint> offset = startFocusPoint - finalFocusPoint;

    // The total amount of time the panning should take (in milliseconds).
    // This could be parameterized later.
    int duration = 700;

    // The number of times per the duration of time that we want to set the
    // intermediate focus point.  This could be parameterized later.
    int step = 15;

    // Amount of time to pause between each intermediate setting of the focus point.
    int wait = duration/step;


    Coordinate<MapPoint> stepOffset(offset.getX()/step, offset.getY()/step);

    for (int stepCv = 0; stepCv < step; stepCv++) {
        
        // Determine the next temporary focus point.
        Coordinate<MapPoint> tempFocusPoint = this->focus - stepOffset;

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

void Map::moveDrawables(Coordinate<MapPoint> offset) {

   std::vector<Drawable*> drawables;

   for (auto itr = moContainer.begin(); itr != moContainer.end(); itr++) {
      drawables.push_back((*itr)->getDrawable());
   }

   GraphicsEngine* ge = GraphicsEngine::getInstance();
   ge->translateDrawablesByOffset(drawables, offset.getX(), offset.getY());
}

void Map::loadBoundingBoxes() {
   Coordinate<MapPoint> tl = this->getTopLeftOfRegion();
   for (int x = 0; x < Map::BOUNDING_BOX_MEM; x++) {
      for (int y = 0; y < Map::BOUNDING_BOX_MEM; y++) {
         Coordinate<MapPoint> bb(
              tl.getX() + x * Map::BOUNDING_BOX_SIZE
            , tl.getY() + y * Map::BOUNDING_BOX_SIZE
         );
         this->loadBoundingBox(bb);
      }
   }
}

void Map::unloadBoundingBoxes() {
   std::vector< Coordinate<MapPoint> >::iterator bbIter = boundingBoxContainer.begin();

   while (bbIter != boundingBoxContainer.end()) {

      if (!isBoundingBoxInScope(*bbIter)) {
         bbIter = boundingBoxContainer.erase(bbIter);
      } else {
         bbIter++;
      }

   }
   this->unloadMapObjects();
}

void Map::loadBoundingBox(Coordinate<MapPoint> bb) {
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

bool Map::isBoundingBoxLoaded(Coordinate<MapPoint> bb) {
   bool alreadyLoaded = false;
   std::vector< Coordinate<MapPoint> >::iterator bbIter;
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
   Drawable* aDrawable = a->getDrawable();
   Drawable* bDrawable = b->getDrawable();

   // Grab an instance of the GraphicsEngine.
   GraphicsEngine* ge = GraphicsEngine::getInstance();

   // Get the Layer of the Drawables for these MapObjects.
   // TODO: We need a stricter relationship between the Map and any layers that
   // it governs.
   Layer* lA = ge->getLayerOfDrawable(aDrawable);
   Layer* lB = ge->getLayerOfDrawable(bDrawable);
   assert(lA == lB);

   if (a->getBottom() > b->getMiddle()) {
      // Put A on Top.
      lA->stackAonB(aDrawable, bDrawable);
   } else {
      // Put B on Top.
      lA->stackAonB(bDrawable, aDrawable);
   }
}

bool Map::isValidBoundingBox(Coordinate<MapPoint> bb) {
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
   std::vector<MapObject*>* map = &(moContainer);

   // Iterate through each MapObject loaded on the Map ...
   std::vector<MapObject*>::iterator moIter = map->begin();
   while (moIter != map->end()) {

      MapObject* mo = *moIter;

      // Is the MapObject in the Region of Relevance?
      if (!this->isMapObjectInScope(mo)) {
         LOG(INFO) << "MapObject not in scope.";

         // Remove the MapObject from the Map; freeing its memory.
         moIter = map->erase(moIter);
      } else {
         moIter++;
      }
   }

}

bool Map::isBoundingBoxInScope(Coordinate<MapPoint> bb) {
   Coordinate<MapPoint> tl = this->getTopLeftOfRegion();
   for (int x = 0; x < Map::BOUNDING_BOX_MEM; x++) {
      for (int y = 0; y < Map::BOUNDING_BOX_MEM; y++) {

         Coordinate<MapPoint> thisBB(
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

   // The CMO is always in scope :-)
   CharacterMapObject* cmo = this->getCharacterMapObject();
   if (mo == cmo) {
      return true;
   }

   // Top Left Corner of MapObject in Question.
   Coordinate<MapPoint> tl = mo->getLeftCorner();

   Coordinate<MapPoint> rr = this->getTopLeftOfRegion();

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

Coordinate<MapPoint> Map::getFocusBoundingBox() {
   // The current focus of the Map.
   Coordinate<MapPoint> f = this->focus;

   // Determine the Bounding Box which contains the focus. (i.e. the Middle)
   int bX = f.getX() - (f.getX() % Map::BOUNDING_BOX_SIZE);
   int bY = f.getY() - (f.getY() % Map::BOUNDING_BOX_SIZE);

   return Coordinate<MapPoint>(bX, bY);
}

Coordinate<MapPoint> Map::getTopLeftOfRegion() {
   Coordinate<MapPoint> bb = this->getFocusBoundingBox();

   // Given the Middle determine the Top Left of the Region of Relevance.
   int middle = Map::BOUNDING_BOX_MEM / 2;
   int tlrrX = bb.getX() - middle * Map::BOUNDING_BOX_SIZE;
   int tlrrY = bb.getY() - middle * Map::BOUNDING_BOX_SIZE;

   return Coordinate<MapPoint>(tlrrX, tlrrY);
}

void Map::adjustDisplay() {

   Coordinate<MapPoint> offset(Screen::WIDTH/2, Screen::HEIGHT/2);
   this->display = this->focus - offset;

   int x = this->display.getX();
   int y = this->display.getY();
   LOG(INFO) << "Set Map Display Point = " << x << ", " << y;	
}

void Map::installMapObject(MapObject* mo, Drawable* d) {
   
   // Install the MapObject.
   moContainer.push_back(mo);

   Coordinate<ScreenPoint> drawableCoord = this->convertWorldToScreen(mo->getLeftCorner());
   int x = drawableCoord.getX();
   int y = drawableCoord.getY();
   d->setX(x);
   d->setY(y);

   GraphicsEngine::getInstance()->displayDrawable(d, "map", x, y);
}

void Map::handle(SDL_Event event) {
   switch (event.type) {
      case SDL_KEYDOWN:
         std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
         break;
      case SDL_MOUSEBUTTONDOWN:

         LOG(INFO) << "Map Click: " << event.button.x << ", " << event.button.y;

         {

            // Delete all boxes in GUI
            GuiFactory::GetInstance()->deleteAll();

            // Translate the SDL_MOUSEBUTTONDOWN into Asgard's move CMO event.
            // Use CANCEL event concurrency policy to prevent multiple user
            // clicks from creating erratic movement.
            Coordinate<MapPoint>* c = new Coordinate<MapPoint>(event.button.x, event.button.y);
            this->fireEvent(ASGARDEVENT_MOVECMO, c, CONCURRENCY_POLICY_CANCEL);

         }


         break;
      case SDL_USEREVENT:

         if (event.user.code == ASGARDEVENT_MAPPAN) {

            Coordinate<MapPoint> *panHereCoord = (Coordinate<MapPoint>*) event.user.data1;

            this->panFocusPoint(panHereCoord->getX(), panHereCoord->getY());

         } else if (event.user.code == ASGARDEVENT_MOVECMO) {

            // Grab the CMO.
            CharacterMapObject* cmo = this->getCharacterMapObject();

            // Get the x/y of the Move CMO Event.
            Coordinate<ScreenPoint>* c = (Coordinate<ScreenPoint>*)event.user.data1;

            // Convert the provided screen coordinate into a world coordinate.
            Coordinate<MapPoint> newCMOWorldCoordinate = convertScreenToWorld(*c);

            // Offset the New World Coordinate by the distance between the Top
            // Left Corner of the CMO and it's foot.  That way, the CMO will
            // arrive at the provided coordinate "on it's foot"
            newCMOWorldCoordinate -= cmo->getFoot() - cmo->getLeftCorner();

            // x & y are the World Coordinate at which the CMO should end up.
            int x = newCMOWorldCoordinate.getX();
            int y = newCMOWorldCoordinate.getY();

            int angle, step, draw_oldX, draw_oldY;
            std::string drawableName, walkingAnimationName, standingAnimationName;
            Drawable *d = cmo->getDrawable();
            std::vector< Coordinate<MapPoint> > path;

            // Get Drawable's name
            drawableName = cmo->getDrawableName();

            // Convert the Drawable's X & Y into a World Coordinate.
            Coordinate<ScreenPoint> drawableOld(d->getX(), d->getY());
            Coordinate<MapPoint> drawableOldMap = convertScreenToWorld(drawableOld);
            draw_oldX = drawableOldMap.getX();
            draw_oldY = drawableOldMap.getY();

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
            // Construct path for CMO to follow
            path = constructPath(cmo->getFoot().getX(), cmo->getFoot().getY(), draw_oldX, draw_oldY, x, y);

            // Increment through path by step, if path exists
            if(!path.empty())
            {
               int i = 0;
               // Prevent from going out of range
               if(step > 1)
               {
                  if((step - 1) >= path.size()) // (step - 1) because first Coordinate in path is one pixel ahead of current position of CMO
                     i = (int)path.size() - 1; 
                  else
                     i = step - 1;
               }

               Coordinate<ScreenPoint> screenLoc;
               bool wasMouseClicked = false;
               while(i < (int)path.size()) 
               {
                  wasMouseClicked = false;

                  // Move MapObject with respect to World Coordinate
                  cmo->move(path[i]);

                  // Move Drawable with respect to Screen Coordinate
                  screenLoc = convertWorldToScreen(path[i]);
                  d->move(screenLoc.getX(),screenLoc.getY());

                  // Restack MapObjects that Intersect.
                  for (auto itr = moContainer.begin(); itr < moContainer.end(); itr++) {
                     if (*itr != cmo) {
                        if (cmo->intersects(*itr)) {
                           this->restack(cmo, *itr);
                        }
                     }
                  }

                  // Check if the CMO is over the Map Pan threshold.  Fire Map Pan
                  // event if so.
                  this->checkOverMapPanThreshold();

                  // Handle any Interactions between the CMO and another MapObject, if necessary
                  for (auto itr = moContainer.begin(); itr < moContainer.end(); itr++)
                  {
                     // TEMPORARY implementation solely for demonstrating Interactions
                     cmo->interacts(*itr,true);
                     // Below implementation will be part of the future permanent solution
                     //cmo->interacts(*itr,(path[i] == newCMOWorldCoordinate));
                  }
                  
                  SDL_Delay(10);

                  i = i + step;
               }
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

/* ---------------------------------------------------------------------------------------------------------------
 * constructPath - Construct path of World Coordinates where to move CMO and its Drawable. Path will contain
 * the Coordinates to which the left corner of the CMO and its Drawable will be set.  The last Coordinate of the
 * path will either be the destination World Coordinate or the last World Coordinate that is not located in a 
 * Hardpoint. Hardpoint conflicts use the CMO's foot for comparison.
 */
std::vector< Coordinate<MapPoint> > Map::constructPath(int moX, int moY, int drawX, int drawY, int destX, int destY) const {
   std::vector< Coordinate<MapPoint> > path;
   int old_moX, old_moY, new_moX, new_moY, old_drawX, old_drawY, new_drawX, new_drawY;
   bool isHardpoint = false;

   old_moX = moX;
   old_moY = moY;
   old_drawX = drawX;
   old_drawY = drawY;
   while((old_drawX != destX) || (old_drawY != destY))
   {
      /* Determine new x location */
      if(old_drawX > destX)
      {
         new_moX = old_moX - 1;
         new_drawX = old_drawX - 1;
      }
      else if(old_drawX < destX)
      {
         new_moX = old_moX + 1;
         new_drawX = old_drawX + 1;
      }
      else
      {
         new_moX = old_moX;
         new_drawX = old_drawX;
      }

      /* Determine new y location */
      if(old_drawY > destY)
      {
         new_moY = old_moY - 1;
         new_drawY = old_drawY - 1;
      }
      else if(old_drawY < destY)
      {
         new_moY = old_moY + 1;
         new_drawY = old_drawY + 1;
      }
      else
      {
         new_moY = old_moY;
         new_drawY = old_drawY;
      }
                     
      /* Create Coordinate to which MapObject is to move */
      Coordinate<MapPoint> newLoc(new_drawX, new_drawY);
      Coordinate<MapPoint> newFoot(new_moX, new_moY);

      /* Check for Hardpoint conflict */
      for (auto itr = moContainer.begin(); itr < moContainer.end(); itr++)
      {
         // Leave loop if Hardpoint detected
         isHardpoint = (*itr)->conflict(newFoot);
         if(isHardpoint)
            break;
      }

      /* Add Coordinate to MapObject path if not Hardpoint */
      if(!isHardpoint)
      {
         path.push_back(newLoc);
         old_moX = new_moX;
         old_drawX = new_drawX;
         old_moY = new_moY;
         old_drawY = new_drawY;
      }
      /* Otherwise, stop CMO at Hardpoint */
      else
         break;
   }

   return path;
}

/* -----------------------------------------------------------------------------
 * convertScreenToWorld - Given a screen coordinate, convert it into a World
 * Coordinate--which is a point on the Map.
 */
Coordinate<MapPoint> Map::convertScreenToWorld(Coordinate<ScreenPoint> s) const {

   // Add the World Coordinate of the current location of the top left corner
   // of the Screen to the provided screen coordinate and return the result.
   int x = this->display.getX() + s.getX();
   int y = this->display.getY() + s.getY();
   return Coordinate<MapPoint>(x, y);

}

/* -----------------------------------------------------------------------------
 * convertWorldToScreen - Given a world coordinate, convert it into a Screen
 * coordinate.  Screen coordinates which are visible to the user are greater
 * than (0,0), but less than the Height and Width of the screen.
 */
Coordinate<ScreenPoint> Map::convertWorldToScreen(Coordinate<MapPoint> w) const {
   
   // The offset between the provided world coordinate and the current display
   // coordinate is equivalent to its Screen Coordinate.
   int x = w.getX() - this->display.getX();
   int y = w.getY() - this->display.getY();
   return Coordinate<ScreenPoint>(x, y);

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
      Coordinate<MapPoint> tLc = cmo->getLeftCorner();
      Coordinate<MapPoint>* panHereCoord = new Coordinate<MapPoint>(tLc.getX(), tLc.getY());
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
   for (auto itr = moContainer.begin(); itr < moContainer.end(); itr++) {

      // In Asgard 0.3.8, there will be only one CharacterMapObject.
      if(dynamic_cast<CharacterMapObject*>(*itr)) {
         cmo = dynamic_cast<CharacterMapObject*>(*itr);
         break;
      }
   }

   return cmo;
}
