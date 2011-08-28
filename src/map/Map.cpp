#include "Map.h"

Map* Map::instance = NULL;

Map::Map() : SystemComponent("map") {

   LOG(INFO) << "Building  Map";
   this->setFocusPoint(Screen::WIDTH/2, Screen::HEIGHT/2);

   Coordinate o(0, 0);
   assert(this->display == o);
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
      LOG(INFO) << "Installing MapObject";
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
}
