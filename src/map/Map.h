#ifndef MAP_H
#define MAP_H

#include <vector>
#include "MapObject.h"
#include "SystemComponent.h"

class Map : public SystemComponent
{
   public:
      ~Map();

      virtual bool open();
      virtual bool close();

      static Map* getInstance();

   private:
      Map();

      std::vector<MapObject*> mapObjectContainer;

      void noop();

      static Map* instance;

      virtual bool interpretMessage(Message* message);
};

#endif//MAP_H
