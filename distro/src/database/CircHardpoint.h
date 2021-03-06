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

#ifndef CIRC_HARDPOINT_H
#define CIRC_HARDPOINT_H

#include "Hardpoint.h"
#include "Coordinate.h"

class MapPoint;

class CircHardpoint : public Hardpoint
{
   private:
      double radius;
   public:
      CircHardpoint();
      ~CircHardpoint();
      CircHardpoint(int x, int y);
      CircHardpoint(int x, int y, double r);

      bool conflict(const Coordinate<MapPoint> & wc, const Coordinate<MapPoint> & moc) const;

};

#endif //CIRC_HARDPOINT_H
