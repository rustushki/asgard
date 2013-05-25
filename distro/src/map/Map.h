#ifndef MAP_H
#define MAP_H

#include "externals.h"
#include "MapObject.h"
#include "Screen.h"
#include "Database.h"
#include "EventHandler.h"
#include "CharacterMapObject.h"
#include "AsgardEvent.h"
#include "ScreenPoint.h"

class Map : public EventHandler {
   public:
      virtual ~Map();

      static Map* getInstance();

      void setFocusPoint(int x, int y);

      void panFocusPoint(int x, int y);

      static const int BOUNDING_BOX_SIZE = 1000;

      // N x N grid of bounding boxes.
      static const int BOUNDING_BOX_MEM  = 3;

      void installMapObject(MapObject* mo, Drawable* d);

      virtual void handle(SDL_Event event);

      Coordinate<ScreenPoint> convertWorldToScreen(Coordinate<MapPoint> w) const;
      Coordinate<MapPoint> convertScreenToWorld(Coordinate<ScreenPoint> s) const;

   private:
      Map();

      Coordinate<MapPoint> display;
      Coordinate<MapPoint> focus;
      std::vector<MapObject*> moContainer;
      std::vector< Coordinate<MapPoint> > boundingBoxContainer;

      // Distance from LEFT, RIGHT, BOTTOM and TOP sides of the screen which
      // when crossed by a CharacterMapObject will cause the firing of a Map
      // Pan event.
      float threshold;

      void adjustDisplay();
      void loadBoundingBoxes();
      void unloadBoundingBoxes();
      void loadBoundingBox(Coordinate<MapPoint> bb);
      void moveDrawables(Coordinate<MapPoint> offset);
      void unloadMapObjects();
      bool isMapObjectInScope(MapObject* mo);
      bool isValidBoundingBox(Coordinate<MapPoint> bb);
      bool isBoundingBoxLoaded(Coordinate<MapPoint> bb);
      bool isBoundingBoxInScope(Coordinate<MapPoint> bb);

      void restack(MapObject* a, MapObject* b) const;

      Coordinate<MapPoint> getFocusBoundingBox();
      Coordinate<MapPoint> getTopLeftOfRegion();

      std::vector< Coordinate<MapPoint> > constructPath(int moX, int moY, int drawX, int drawY, int destX, int destY) const;

      void checkOverMapPanThreshold() const;
      CharacterMapObject* getCharacterMapObject() const;

      static Map* instance;
};

#endif//MAP_H
