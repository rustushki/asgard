/*****************************************************************************
 * Copyright (c) 2013 Russ Adams, Sean Eubanks, Asgard Contributors
 * This file is part of Asgard.
 *
 * Asgard is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asgard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Asgard; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/

#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "externals.h"
#include "Hardpoint.h"
#include "Coordinate.h"
#include "MapObjectState.h"
#include "Interactionpoint.h"
#include "Interaction.h"
#include "Drawable.h"
#include "Inventory.h"

#define MAP_OBJECT_HEIGHT_DEFAULT   10
#define MAP_OBJECT_WIDTH_DEFAULT    10

using std::list;

class MapObject
{
   public:
      MapObject(Drawable* drawable);
      virtual ~MapObject();
      
      void setLeftCorner(const Coordinate<MapPoint>& leftCorner);
      Coordinate<MapPoint> getLeftCorner() const;
      uint getHeight() const;
      uint getWidth() const;

      int getMiddle() const;
      int getBottom() const;
      int getTop() const;
      int getLeft() const;
      int getRight() const;
      Coordinate<MapPoint> getFoot() const;

      std::string getDrawableName() const;
      
      void addHardpoint(Hardpoint *hardpoint);
      bool conflict(Coordinate<MapPoint> c);
      bool intersects(MapObject*);

      void addInteractionpoint(Interactionpoint *interactionpoint);

      // Determines if this MapObject is within one of the accepter's Interactionpoints.
      // If so, then the accepter will allow its Interactions to be handled.
      void interacts(MapObject *accepter, bool wasMouseClicked);

      void addInteraction(Interaction *interaction);

      int computeAngleOfMovement(int newX, int newY, int oldX, int oldY);

      void move(Coordinate<MapPoint> newLoc);
      void move(int newX, int newY);

      void setState(MapObjectState state);
      MapObjectState getState();
      void setStep(int step);
      int getStep();

      // WORKAROUND: MapObject will contain a pointer to its Drawable but not necessarily in this fashion
      void setDrawable(Drawable *d);
      Drawable *getDrawable() const;

   private:
      Coordinate<MapPoint> leftCorner;
      list<int> boundingBoxes;
      std::string drawableName;
      Drawable *drawable; // WORKAROUND: MapObject will contain a pointer to its Drawable but not necessarily in this fashion

      std::vector<Hardpoint*> hardpoints;
      std::vector<Interactionpoint*> interactionpoints;
      std::vector<Interaction*> interactions;

      MapObjectState state;
      int step;
};
#endif//MAP_OBJECT_H
