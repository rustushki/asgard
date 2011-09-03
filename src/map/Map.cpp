#include "Map.h"

Map* Map::instance = NULL;

Map::Map() : SystemComponent("map") {
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

bool Map::open()
{
   bool status = true;

   this->thread->open(boost::bind(&Map::noop, this));
   
   status = SystemComponent::open();
   
   return status;
}

bool Map::close()
{
   bool status = true;
   
   if(!this->thread->isClosed())
   {
      this->thread->close();
   }
   
   status = SystemComponent::close();
   
   return status;
}

void Map::noop()
{
   // Wait until a message is received.
   this->listen(-1);
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

   this->focus = Coordinate(x, y);
   this->adjustDisplay();
   this->loadBoundingBoxes();
   this->unloadDrawables();
}

void Map::loadBoundingBoxes() {
   for (int x = 0; x < Map::BOUNDING_BOX_MEM; x++) {
      for (int y = 0; y < Map::BOUNDING_BOX_MEM; y++) {
         MessageFactory::makeLoadBoundingBox(x*Map::BOUNDING_BOX_SIZE, y*Map::BOUNDING_BOX_SIZE);
      }
   }
}

void Map::unloadDrawables() {
   std::vector<MapObject*>::iterator moIter;

   for (moIter = this->mapObjectContainer.begin(); moIter != this->mapObjectContainer.end(); moIter++) {

      if (!this->isMapObjectInScope(*moIter)) {
         LOG(INFO) << "MapObject not in scope.  Unloading...";

         MapObject* mo = *moIter;

         // TODO: Unload MapObject

         // TODO: Don't have this message type yet.
         //MessageFactory::makeUnloadDrawable(mo->getDrawableName());
      }
   }
}

bool Map::isMapObjectInScope(MapObject* mo) {

   // Top Left Corner of MapObject in Question.
   Coordinate tl = mo->getLeftCorner();

   // The current focus of the Map.
   Coordinate f = this->focus;

   // Determine the Bounding Box which contains the focus. (i.e. the Middle)
   int bX = f.getX() - (f.getX() % Map::BOUNDING_BOX_SIZE);
   int bY = f.getY() - (f.getY() % Map::BOUNDING_BOX_SIZE);

   // Given the Middle determine the Top Left of the Region of Relevance.
   int middle = Map::BOUNDING_BOX_MEM / 2;
   int tlrrX = bX - middle * Map::BOUNDING_BOX_SIZE;
   int tlrrY = bY - middle * Map::BOUNDING_BOX_SIZE;

   // Determine Dimensions of Region of Relevance
   int rrSize = Map::BOUNDING_BOX_SIZE*Map::BOUNDING_BOX_MEM;

   // If the MapObject is x dimensionally out of bounds...
   if (tl.getX() > tlrrX + rrSize || tl.getX() < tlrrX) {
      // Out of Scope.
      return false;
   }

   // If the MapObject is y dimensionally out of bounds...
   if (tl.getY() > tlrrY + rrSize || tl.getY() < tlrrY) {
      // Out of Scope.
      return false;
   }

   // Otherwise, in Scope.
   return true;
}

void Map::adjustDisplay() {

   Coordinate offset(Screen::WIDTH/2, Screen::HEIGHT/2);
   this->display = this->focus - offset;

   int x = this->display.getX();
   int y = this->display.getY();
   LOG(INFO) << "Set Map Display Point = " << x << ", " << y;	
}

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
