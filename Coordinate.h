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

#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
   public:
      Coordinate();
      Coordinate(int x, int y);
      Coordinate(const Coordinate&);

      void operator+= (const Coordinate);
      void operator-= (const Coordinate);

      Coordinate operator+ (const Coordinate) const;
      Coordinate operator- (const Coordinate) const;
      
      // scaling arithmetic
      Coordinate operator+ (const int) const;
      Coordinate operator- (const int) const;
      Coordinate operator* (const int) const;
      Coordinate operator/ (const int) const;
      //friend Coordinate operator+(const Coordinate&, const Coordinate&);

      bool operator== (const Coordinate) const;
      bool operator!= (const Coordinate) const;

      friend double distance(const Coordinate&,const Coordinate&); 

   private:
      int x,y;
};
#endif //COORDINATE_H
