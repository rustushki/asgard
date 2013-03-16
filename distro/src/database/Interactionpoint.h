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
#include "Coordinate.h"

#ifndef INTERACTIONPOINT_H
#define INTERACTIONPOINT_H

class Interactionpoint
{
   protected:
      Coordinate coordinate;
      bool requiresMouseClick; // Handle Interactions whether or not user clicks within point

   public:
      virtual bool conflict(const Coordinate&,const Coordinate &) const = 0;
      virtual void setRequiresMouseClick(bool requiresMouseClick) = 0;
      virtual bool getRequiresMouseClick() const = 0;

      virtual ~Interactionpoint() {};
};

enum INTERACTIONPOINT_TYPE
{
   INTERACTIONPOINT_TYPE_RECT,
   INTERACTIONPOINT_TYPE_CIRC,
   INTERACTIONPOINT_TYPE_COUNT
};

#endif //INTERACTIONPOINT_H
