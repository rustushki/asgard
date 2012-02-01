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

#include "MobileMapObject.h"

MobileMapObject::MobileMapObject(std::string drawableName) : StaticMapObject(drawableName) {

}

MobileMapObject::~MobileMapObject() {

}


/***********************************************************
 * move - Given a newX and a newY, do several things: 
 *
 * 1. Update MobileMapObject state to 'moving'.  'state' is an enumerated type
 *    member of MobileMapObject.  It may be 'idle' or 'moving'.
 * 2. Compute the angle of movement using Pythagorean Theorem.
 * 3. Use the angle of movement to determine the animation to swap in for the
 *    Drawable. 
 * 4. Instruct the associated drawable to move Step by Step across the map in a
 *    loop.  Step is a member of MobileMapObject.  Step is an integral distance.
 * 5. Sleep a certain duration between each movement of the Drawable so that
 *    the user has time to see the Drawable move.
 * 6. Update the MapObject's World Coordinate each iteration of the loop.
 *
 * Points #4-6 are OK because 'move()' must be run in an event thread (thus it
 * won't block the main thread of execution).
 */
void MobileMapObject::move(int newX, int newY) {

   // TODO: we should probably enforce that this run inside a special thread,
   // but it's unclear how to discern threads right now.  feel free to leave
   // this here as a cautionary tale to the next programmer.
   
   // TODO: implement the above 6 points.

   // Computational Handwaving.
}
