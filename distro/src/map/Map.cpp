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
#include "CharacterMapObject.h"

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
      cmo->setWidth(100);
      cmo->setHeight(100);

      // x = 300, y = 300 puts this CMO in BB (0, 0)
      cmo->setLeftCorner(Coordinate(300,400));

      this->installMapObject(cmo, d);

      // Useful for testing animations ...
      //d->swapAnimation("NotMatchWalkingEast");

   // END -- CODE THAT DOES NOT BELONG HERE
   //


}

Map::~Map() {

}

Map* Map::getInstance() {
   if (instance == NULL)
      instance = new Map();

   return instance;
}

void Map::setFocusPoint(int x, int y) {

   if (x < 0) {
      x = 0;
   }

   if (y < 0) {
      y = 0;
   }

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

   GraphicsEngine::getInstance()->displayDrawable(d, "stageLayer", x, y);
}

void Map::handle(SDL_Event event) {
   switch (event.type) {
      case SDL_KEYDOWN:
         std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
         break;
      case SDL_MOUSEBUTTONDOWN:
         //event.button.button, event.button.x, event.button.y
         std::cout << event.button.x << ", " << event.button.y << std::endl;

         // As it turns out, you can't declare variables inside a switch case
         // unless you restrict the scope with {}
         {

            // Get the x/y of the mouse click event.
            int x = event.button.x;
            int y = event.button.y;

            // Iterate over MapObjects on the Map.  Find the one which is the
            // CharacterMapObject and move it to the provided x/y.
            std::vector<MapObject*>::iterator itr;
            for (itr = mapObjectContainer.begin(); itr < mapObjectContainer.end(); itr++) {

               // In Asgard 0.3.7, there will be only one CharacterMapObject.
               if(dynamic_cast<CharacterMapObject*>(*itr)) {
                  (*itr)->move(x, y);
                  break;
               }
            }
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
Coordinate Map::convertScreenToWorld(Coordinate s) {

   // Add the World Coordinate of the current location of the top left corner
   // of the Screen to the provided screen coordinate and return the result.
   return (this->display + s);

}

/* -----------------------------------------------------------------------------
 * convertWorldToScreen - Given a world coordinate, convert it into a Screen
 * coordinate.  Screen coordinates which are visible to the user are greater
 * than (0,0), but less than the Height and Width of the screen.
 */
Coordinate Map::convertWorldToScreen(Coordinate w) {
   
    // The offset between the provided world coordinate and the current display
    // coordinate is equivalent to its Screen Coordinate.
    return (w - this->display);

}
