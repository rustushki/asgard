#ifndef MAP_H
#define MAP_H

#include <vector>
#include <cassert>
#include "MapObject.h"
#include "MessageFactory.h"
#include "SystemComponent.h"
#include "Screen.h"

class Map : public SystemComponent
{
   public:
      ~Map();

      virtual bool open();
      virtual bool close();

      static Map* getInstance();

      void setFocusPoint(int x, int y);

   private:
      Map();

      Coordinate display;
      Coordinate focus;
      std::vector<MapObject*> mapObjectContainer;

      void noop();
      void adjustDisplay();

      static Map* instance;

      virtual bool interpretMessage(Message* message);
};

#endif//MAP_H
