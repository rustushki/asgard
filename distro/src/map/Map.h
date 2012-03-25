#ifndef MAP_H
#define MAP_H

#include "externals.h"
#include "MapObject.h"
#include "Screen.h"
#include "Database.h"
#include "EventHandler.h"

class Map : public EventHandler {
   public:
      ~Map();

      static Map* getInstance();

      void setFocusPoint(int x, int y);

      static const int BOUNDING_BOX_SIZE = 1000;

      // N x N grid of bounding boxes.
      static const int BOUNDING_BOX_MEM  = 3;

      void installMapObject(MapObject* mo, Drawable* d);

      virtual void handle(SDL_Event event);

      Coordinate convertWorldToScreen(Coordinate w);
      Coordinate convertScreenToWorld(Coordinate s);

   private:
      Map();

      Coordinate display;
      Coordinate focus;
      std::vector<MapObject*> mapObjectContainer;
      std::vector<Coordinate> boundingBoxContainer;

      // Distance from LEFT, RIGHT, BOTTOM and TOP sides of the screen which
      // when crossed by a CharacterMapObject will cause the firing of a Map
      // Pan event.
      float threshold;

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
};

#endif//MAP_H
