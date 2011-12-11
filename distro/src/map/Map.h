#ifndef MAP_H
#define MAP_H

#include "externals.h"
#include "MapObject.h"
#include "Screen.h"
#include "Database.h"

class Map
{
   public:
      ~Map();

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
      std::vector<Coordinate> boundingBoxContainer;

      void noop();
      void adjustDisplay();
      void loadBoundingBoxes();
      void unloadBoundingBoxes();
      void loadBoundingBox(Coordinate bb);
      void moveDrawables(Coordinate offset);
      void unloadMapObjects();
      bool isMapObjectInScope(MapObject* mo);
      bool isValidBoundingBox(Coordinate bb);
      bool isBoundingBoxLoaded(Coordinate bb);
      bool isBoundingBoxInScope(Coordinate bb);
      Coordinate getFocusBoundingBox();
      Coordinate getTopLeftOfRegion();

      static Map* instance;

/*
      virtual bool interpretMessage(Message* message);
      void handleMoveFocusPoint(Message* message);
      void handleInstallMapObject(Message* message);
*/

};

#endif//MAP_H
