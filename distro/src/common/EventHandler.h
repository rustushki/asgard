/*****************************************************************************
 * Copyright (c) 2012 Russ Adams, Sean Eubanks, Asgard Contributors
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
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "externals.h"
#include "AsgardEvent.h"
#include "ConcurrencyPolicy.h"

/* EventHandler - Abstract interface class. Implement this interface in order
 * to handle Events.
 */

class EventHandler {

public:
   // Pass an event
   virtual void handle(SDL_Event event) = 0;

   void fireEvent(AsgardEvent eventCode, void* eventData, ConcurrencyPolicy policy) const;

};

#endif//EVENTHANDLER_H
