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
#include "AsgardMode.h"
#include "AsgardEvent.h"
#include "ISaveable.h"

class Console;
class GraphicsEngine;
class GuiFactory;
class EventHandler;
class Map;
class Database;
class ResourceLoader;

class Asgard {
   public:

      // Asgard is singleton.
      static Asgard* getInstance();

      // De-inits Externals
      ~Asgard();

      // Starts View and Controller threads.
      void start();

      // Gates the Controller from starting until the View thread unlocks.
      boost::condition_variable gate;

      // argv and argc from program launch.
      static char** argv;
      static int argc;

      // Get the Mode of Operation.
      AsgardMode getMode();

      // Return the event handler currently accepting events, or NULL if there
      // is none.
      EventHandler* getEventHandler();

      // Save the current state of the game.
      void save();

      // Load a game state file.
      void load();

      // Register an object that implements ISaveable so that Asgard::save()
      // may write it to the save file.
      void registerSaveable(std::shared_ptr<ISaveable> is);

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

      // Mapping of AsgardEvent Types to Thread IDs.
      std::map<AsgardEvent, boost::thread*> asgardEventToThread;

      // Asgard memory manages these singleton components.
      std::unique_ptr<GraphicsEngine> ge;
      std::unique_ptr<Database>       db;
      std::unique_ptr<Map>            mp;
      //std::unique_ptr<Console>        co;
      std::unique_ptr<GuiFactory>     gf;
      std::unique_ptr<ResourceLoader> rl;

      // Registered ISaveable objects
      std::vector<std::shared_ptr<ISaveable>> saveables;
};

#endif//ASGARD_H
