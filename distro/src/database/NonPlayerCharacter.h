/*****************************************************************************
 * Copyright (c) 2007 Russ Adams, Sean Eubanks, Asgard Contributors
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

#ifndef NON_PLAYER_CHARACTER_H
#define NON_PLAYER_CHARACTER_H

#include "externals.h"
#include "MapObject.h"

#define NON_PLAYER_CHARACTER_DEFAULT_SPEED   0

class NonPlayerCharacter : public MapObject
{
   public:
      NonPlayerCharacter(Drawable* drawable);
      ~NonPlayerCharacter();
      
      void setSpeed(int speed);
      void addCoordinateToPath(Coordinate<MapPoint> *coordinate);
   private:
      std::vector< Coordinate<MapPoint>* > path;
      int speed;
};

#endif //NON_PLAYER_CHARACTER_H
