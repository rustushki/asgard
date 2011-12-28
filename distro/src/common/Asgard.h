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
#ifndef ASGARD_H
#define ASGARD_H

#include "externals.h"
#include "Screen.h"
#include "Console.h"
#include "GraphicsEngine.h"
#include "Database.h"
#include "Map.h"
#include "AsgardMode.h"

class Asgard {
   public:

      // Asgard is singleton.
      static Asgard* getInstance();

      // De-inits Externals
      ~Asgard();

      // Starts View and Controller threads.
      void start();

      // Gates the Controller from starting until the View thread unlocks.
      boost::mutex gate;

      // argv and argc from program launch.
      static char** argv;
      static int argc;

      // Get the Mode of Operation.
      AsgardMode getMode();

   private:

      // Instance for Singleton.
      static Asgard* instance;

      // Constructor.
      Asgard();

      // Mode of Operation. The Mode determines which components should handle
      // events.
      AsgardMode mode;

      // Start any External Dependencies.
      void initExternal();

      // Build Model (Asgard's Components).
      void initModel();

      // Threads Methods
      void controller();
      void view();
};

#endif//ASGARD_H
