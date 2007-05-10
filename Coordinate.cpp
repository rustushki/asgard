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
#include <cmath>
#include "Coordinate.h"

Coordinate::Coordinate()
{
   //Initialize to zero
   this->x = 0;
   this->y = 0;
}

Coordinate::Coordinate(int x, int y)
{
   this->x = x;
   this->y = y;
}

Coordinate::Coordinate(const Coordinate & c)
{
   this->x = c.x;
   this->y = c.y;
}

void Coordinate::operator+=(const Coordinate x)
{
   this->x += x.x;
   this->y += x.y;
}

void Coordinate::operator-=(const Coordinate x)
{
   this->x -= x.x;
   this->y -= x.y;
}

bool Coordinate::operator==(const Coordinate x) const
{
   if (x.x != this->x) return false;
   if (x.y != this->y) return false;
   return true;
}

bool Coordinate::operator!=(const Coordinate x) const
{
   return !(*this == x);
}

Coordinate Coordinate::operator+ (const Coordinate x) const
{
   return Coordinate(this->x+x.x, this->y+x.y);
}


Coordinate Coordinate::operator- (const Coordinate x) const
{
   return Coordinate(this->x-x.x, this->y-x.y);
}

Coordinate Coordinate::operator+ (const int x) const
{
   return Coordinate(this->x+x, this->y+x);
}

Coordinate Coordinate::operator- (const int x) const
{
   return Coordinate(this->x-x, this->y-x);
}

Coordinate Coordinate::operator* (const int x) const
{
   return Coordinate(this->x*x, this->y*x);
}

Coordinate Coordinate::operator/ (const int x) const
{
   return Coordinate(this->x/x, this->y/x);
}

Coordinate operator+(const int r, const Coordinate& l)
{
   return Coordinate(r+l.x,r+l.y);
}

double distance(const Coordinate &l, const Coordinate &r)
{
   return std::sqrt(std::pow(double(l.x - r.x), 2) + std::pow(double(l.y - r.y),2));
}
