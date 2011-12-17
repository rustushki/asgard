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

#include "Asgard.h"

Asgard* Asgard::instance = NULL;
int     Asgard::argc     = 0;
char**  Asgard::argv     = NULL;

Asgard* Asgard::getInstance() {
   if (Asgard::instance == NULL) {
      Asgard::instance = new Asgard();
   }

   return Asgard::instance;
}

Asgard::Asgard() {
   LOG(INFO) << "Initting Externals...";
   this->initExternal();

   LOG(INFO) << "Initting Model...";
   this->initModel();
}

void Asgard::initModel() {
   GraphicsEngine::getInstance();
   Database::getInstance();
   Map::getInstance();
   Console::getInstance();
}

void Asgard::controller() {
   LOG(INFO) << "Controller Thread started";

   // Block until View ungates the Controller.
   this->gate.lock();

   // The View is now ready.

   // Read from the Console.
   Console::getInstance()->inputLoop();
}

void Asgard::view() {
   LOG(INFO) << "View Thread started";

   // Start the Graphics Engine page flip loop.
   GraphicsEngine::getInstance()->play();

}

void Asgard::initExternal() {
   // Initialize SDL
   SDL_Init(SDL_INIT_VIDEO);
   SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, 16, SDL_DOUBLEBUF);

   // Initialize Google Logger.
   google::InitGoogleLogging("asgard");

   // Initialize Python
   Py_Initialize();

   if (Py_IsInitialized() != true) {
      std::cout << "Python failed to initialize." << std::endl;
      exit(0);
   }

   Py_InitModule("asgard", AsgardMethods);
   Py_InitModule("map",    MapMethods);
}

Asgard::~Asgard() {
   Py_Finalize();
   SDL_Quit();
}

/* Starts Controller and View threads.
 *
 * @return
 */
void Asgard::start() {
   // Gate the Controller Thread.
   this->gate.lock();

   // Activate the View Thread.
   boost::thread viewThread(&Asgard::view, this);

   // Activate the Controller Thread.
   boost::thread contThread(&Asgard::controller, this);

   // Wait for them to both to end.
   viewThread.join();
   contThread.join();
}


