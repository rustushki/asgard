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

#include "RectHardpoint.h"

RectHardpoint::RectHardpoint()
{
   this->coordinate = Coordinate<MapPoint>(0,0);
   this->height = 0;
   this->width = 0;
}

RectHardpoint::RectHardpoint(int x, int y, int height, int width)
{
   this->coordinate = Coordinate<MapPoint>(x,y);
   this->height = height;
   this->width = width;
}

RectHardpoint::~RectHardpoint()
{
}

bool RectHardpoint::conflict(const Coordinate<MapPoint> & wc, const Coordinate<MapPoint> & moc) const
{
   Coordinate<MapPoint> br; 
   Coordinate<MapPoint> tl = this->coordinate + moc;
   br = tl + Coordinate<MapPoint>(this->width, this->height);

   if((wc.getX() > tl.getX()) && (wc.getY() > tl.getY()) && (wc.getX() < br.getX()) && (wc.getY() < br.getY()))
      return true;
   else
      return false;
}
