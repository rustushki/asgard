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

#ifndef COORDINATE_H
#define COORDINATE_H

#include "externals.h"

template <class P>
class Coordinate
{
   public:
      Coordinate() {
         //Initialize to zero
         this->x = 0;
         this->y = 0;
      }

      Coordinate(int x, int y) {
         this->x = x;
         this->y = y;
      }

      Coordinate(const Coordinate<P>& copyme) {
         this->x = copyme.x;
         this->y = copyme.y;
      }

      void operator+= (const Coordinate<P> rhwc) {
         this->x += rhwc.x;
         this->y += rhwc.y;
      }

      void operator-= (const Coordinate<P> rhwc) {
         this->x -= rhwc.x;
         this->y -= rhwc.y;
      }

      Coordinate operator+ (const Coordinate<P> rhwc) const {
         return Coordinate<P>(this->x+rhwc.x, this->y+rhwc.y);
      }

      Coordinate operator- (const Coordinate<P> rhwc) const {
         return Coordinate(this->x-rhwc.x, this->y-rhwc.y);
      }
      
      // scaling arithmetic
      Coordinate<P> operator+ (const int scalar) const {
         return Coordinate(this->x+scalar, this->y+scalar);
      }

      Coordinate<P> operator- (const int scalar) const {
         return Coordinate(this->x-scalar, this->y-scalar);
      }

      Coordinate<P> operator* (const int scalar) const {
         return Coordinate(this->x*x, this->y*x);
      }

      Coordinate<P> operator/ (const int scalar) const {
         return Coordinate(this->x/x, this->y/x);
      }

      friend Coordinate<P> operator+(const int scalar, const Coordinate<P>& wc) {
         return Coordinate<P>(scalar+wc.x,scalar+wc.y);
      }

      friend Coordinate<P> operator-(const int scalar, const Coordinate<P>& wc) {
         return Coordinate<P>(scalar-wc.x,scalar-wc.y);
      }

      friend Coordinate<P> operator*(const int scalar, const Coordinate<P>& wc) {
         return Coordinate<P>(scalar*wc.x,scalar*wc.y);
      }

      friend Coordinate<P> operator/(const int scalar, const Coordinate<P>& wc) {
         return Coordinate<P>(scalar/wc.x,scalar/wc.y);
      }

      bool operator== (const Coordinate<P> rhwc) const {
         if (rhwc.x != this->x) return false;
         if (rhwc.y != this->y) return false;
         return true;
      }

      bool operator!= (const Coordinate<P> rhwc) const {
         return !(*this == rhwc);
      }

      bool operator>  (const Coordinate<P> rhwc) const {
         return !(*this <= rhwc);
      }

      bool operator<  (const Coordinate<P> rhwc) const {
         return !(*this >= rhwc);
      }

      bool operator<= (const Coordinate<P> rhwc) const {
         return (this->x <= rhwc.x && this->y <= rhwc.y);
      }

      bool operator>= (const Coordinate<P> rhwc) const {
         return (this->x >= rhwc.x && this->y >= rhwc.y);
      }

      int getX() const {
         return this->x;
      }

      int getY() const {
         return this->y;
      }

      friend double distance(const Coordinate<P>& l,const Coordinate<P>& r) {
         return std::sqrt(std::pow(double(l.x - r.x), 2) + std::pow(double(l.y - r.y),2));
      }

   protected:
      int x,y;

};
#endif //COORDINATE_H
