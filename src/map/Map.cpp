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

}

bool Map::interpretMessage(Message* message)
{
}
