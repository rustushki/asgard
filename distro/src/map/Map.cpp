#include "Map.h"

Map* Map::instance = NULL;

Map::Map() {
   LOG(INFO) << "Building  Map";
}

Map::~Map()
{

}

Map* Map::getInstance()
{
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

   this->focus = newFocus;
   this->adjustDisplay();
   this->loadBoundingBoxes();
   this->unloadBoundingBoxes();
   this->moveDrawables(offset);
}

void Map::moveDrawables(Coordinate offset) {

   std::vector<std::string>* drawableNames = new std::vector<std::string>();

   std::vector<MapObject*>::iterator moIter;
   for (moIter = this->mapObjectContainer.begin(); moIter != this->mapObjectContainer.end(); moIter++) {
      drawableNames->push_back((*moIter)->getDrawableName());
   }

   //MessageFactory::makeTranslateDrawablesByOffset(drawableNames, offset.getX(), offset.getY());
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

         // Send UnloadDrawable message to Graphics Engine.
         //MessageFactory::makeUnloadDrawable(mo->getDrawableName());

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

/*
bool Map::interpretMessage(Message* message)
{
   if (message->header.type == MESSAGE_TYPE_INSTALL_MAP_OBJECT) {
      LOG(INFO) << "Received InstallMapObject";
      this->handleInstallMapObject(message);
   } else if (message->header.type == MESSAGE_TYPE_MOVE_FOCUS_POINT) {
      LOG(INFO) << "Received MoveFocusPoint Message.";
      this->handleMoveFocusPoint(message);      
   }
}

void Map::handleMoveFocusPoint(Message* message) {
   int x = message->data.moveFocusPoint.X;
   int y = message->data.moveFocusPoint.Y;
   this->setFocusPoint(x, y);
}

void Map::handleInstallMapObject(Message* message) {
   // Get the two parameters for InstallMapObject
   MapObject* mo = message->data.installMapObject.mapObjectPtr;
   Drawable* d = message->data.installMapObject.drawPtr;

   // Install the MapObject.
   this->mapObjectContainer.push_back(mo);

   Coordinate drawableCoord = mo->getLeftCorner() - this->display;
   int x = drawableCoord.getX();
   int y = drawableCoord.getY();

   LOG(INFO) << "Displaying Drawable " << d->getInstanceName();
   // Now DisplayDrawable
   MessageFactory::makeDisplayDrawable(d, "stageLayer", x, y);
}
*/
