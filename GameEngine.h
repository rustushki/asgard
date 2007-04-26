/*****************************************************************************
 * Copyright (c) 2006 Russ Adams, Sean Eubanks, Asgard Contributors
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

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include "Coordinate.h"

#define VISIBLE_BOUNDING_BOXES   9

class GameEngine
{
   public:
      static GameEngine* getInstance();
      void loadGame();
      void loadVisibleBoxes();
      void addMapObject(MapObject object);
      void removeBoundingBoxObjects(int boundingBoxID);
      
   private:
      GameEngine();
      static GameEngine* instance;
      std::vector<MapObject> objects;
      int visibleBoxes[VISIBLE_BOUNDING_BOXES];
      Coordinate currentPosition;
};

#endif //GAME_ENGINE_H

