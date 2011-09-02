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

      static const int BOUNDING_BOX_SIZE = 1000;

      // N x N grid of bounding boxes.
      static const int BOUNDING_BOX_MEM  = 3;

   private:
      Map();

      Coordinate display;
      Coordinate focus;
      std::vector<MapObject*> mapObjectContainer;

      void noop();
      void adjustDisplay();
      void loadBoundingBoxes();

      static Map* instance;

      virtual bool interpretMessage(Message* message);
      void handleMoveFocusPoint(Message* message);
      void handleInstallMapObject(Message* message);
};

#endif//MAP_H
