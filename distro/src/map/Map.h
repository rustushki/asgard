#ifndef MAP_H
#define MAP_H

#include "externals.h"
#include "Coordinate.h"
#include "EventHandler.h"
class CharacterMapObject;
class Drawable;
class MapPoint;
class MapObject;
class ScreenPoint;

class Map : public EventHandler {
   public:
      virtual ~Map();

      static Map* getInstance();

      void setFocusPoint(int x, int y);

      void panFocusPoint(int x, int y);

      static const int BOUNDING_BOX_SIZE = 1000;

      // N x N grid of bounding boxes.
      static const int BOUNDING_BOX_MEM  = 3;

      void installMapObject(std::shared_ptr<MapObject> mo, Drawable* d);

      virtual void handle(SDL_Event event);

      Coordinate<ScreenPoint> convertWorldToScreen(Coordinate<MapPoint> w) const;
      Coordinate<MapPoint> convertScreenToWorld(Coordinate<ScreenPoint> s) const;

   private:
      Map();

      Coordinate<MapPoint> display;
      Coordinate<MapPoint> focus;
      std::vector< std::shared_ptr<MapObject> > moContainer;
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
      bool isMapObjectInScope(std::shared_ptr<MapObject> mo);
      bool isValidBoundingBox(Coordinate<MapPoint> bb);
      bool isBoundingBoxLoaded(Coordinate<MapPoint> bb);
      bool isBoundingBoxInScope(Coordinate<MapPoint> bb);

      void restack(std::shared_ptr<MapObject> a, std::shared_ptr<MapObject> b) const;

      Coordinate<MapPoint> getFocusBoundingBox();
      Coordinate<MapPoint> getTopLeftOfRegion();

      std::vector< Coordinate<MapPoint> > constructPath(int moX, int moY, int drawX, int drawY, int destX, int destY) const;

      void checkOverMapPanThreshold() const;
      std::shared_ptr<CharacterMapObject> getCharacterMapObject() const;

      static Map* instance;
};

#endif//MAP_H
