#include "MessageFactory.h"
#include "Map.h"

Map* Map::instance = NULL;

Map::Map() : SystemComponent("map")
{

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

bool Map::interpretMessage(Message* message)
{
   if (message->header.type == MESSAGE_TYPE_INSTALL_MAP_OBJECT) {
	  // Get the two parameters for InstallMapObject
	  MapObject* mo = message->data.installMapObject.mapObjectPtr;
	  Drawable* d = message->data.installMapObject.drawPtr;

	  // Install the MapObject.
	  this->mapObjectContainer.push_back(mo);

	  // Now DisplayDrawable
	  MessageFactory::makeDisplayDrawable(d, "stageLayer");
   }
}
