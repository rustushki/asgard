/*****************************************************************************
 * Copyright (c) 2011 Russ Adams, Sean Eubanks, Asgard Contributors
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
#ifndef  ASGARDMODE_H
#define  ASGARDMODE_H

// AsgardMode -
// These are the modes of operation for the game.  Modes are used for event
// handling and thread synchronization.  The first two are special modes
// pertaining to starting and ending the game.  The rest should be used to
// indicate the Model Component which is currently accepting events.

// Only the Controller thread may set the Mode of Operation.

enum AsgardMode {
     ASGARDMODE_STARTING  // Initializing the Model.
   , ASGARDMODE_QUITTING  // Waiting for Threads to End.
   , ASGARDMODE_MAP       // Displaying and Interacting with the Map
   , ASGARDMODE_COUNT
};

#endif// ASGARDMODE_H
