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
}

void Map::loadBoundingBoxes() {
   MessageFactory::makeLoadBoundingBox(0,0);

// TODO: Determine which bounding boxes need to be loaded and unloaded.  Do
// said loading and unloading.  This code below is a good starting point.
/*
   for (int x = 0; x < Map::BOUNDING_BOX_MEM; x++) {
      for (int y = 0; y < Map::BOUNDING_BOX_MEM; y++) {
         MessageFactory::makeLoadBoundingBox(x*Map::BOUNDING_BOX_SIZE, y*Map::BOUNDING_BOX_SIZE);
      }
   }
*/
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
