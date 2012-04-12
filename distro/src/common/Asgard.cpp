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

#include "Asgard.h"
#include "ConsolePython.h"

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
   this->initExternal();

   // Can't output before initting externals since GLOG is one of the
   // externals.
   LOG(INFO) << "Initted Externals...";

   LOG(INFO) << "Initting Model...";

   this->mode = ASGARDMODE_STARTING;

   this->initModel();

   this->mode = ASGARDMODE_MAP;
}

void Asgard::initModel() {
   GraphicsEngine::getInstance();
   Database::getInstance();
   Map::getInstance();
   Console::getInstance();
}

void Asgard::controller() {
   LOG(INFO) << "Controller Thread started";

   // Lock to use with the gate.
   boost::mutex m;
   boost::mutex::scoped_lock lock(m);

   // Block until View ungates the Controller.
   this->gate.wait(lock);

   // The View is now ready.

   // Read from the Console and Process all Input.
   Console::getInstance()->inputLoop();

   // Wait for Events
   LOG(INFO) << "Waiting for Events ...";

   SDL_Event event;

   // Event Handling Loop (EHL)
   while (true) {
      // Wait for another event. Blocks.
      SDL_WaitEvent(&event);

      switch (event.type) {
         
         // Handle the Quit Event.
         case SDL_QUIT:

            // Set mode to Quiting and exit Controller thread.  Other threads
            // will synchronize on the mode of operation.
            this->mode = ASGARDMODE_QUITTING;
            return;

            // Good form.
            break;

         // All Else: Get the Current Event Handler and have it handle the
         // event.
         case SDL_MOUSEBUTTONDOWN:
         case SDL_USEREVENT:

            {

            EventHandler* eh = this->getEventHandler();
            if (eh == NULL) {
               break;
            }

            // SDL USER EVENTS are treated as special Asgard Events.  See
            // EventHandler.h for more details on Firing Events and Concurrency
            // Policies.

            // Pre-Event Handling Thread Start Checks.
            if (event.type == SDL_USEREVENT) {

               // Get the Asgard Event Type and Concurrency Policy.
               AsgardEvent eventCode = (AsgardEvent)event.user.code;
               ConcurrencyPolicy* policy = (ConcurrencyPolicy*)event.user.data2;

               // CANCEL concurrency policy.
               if (*policy == CONCURRENCY_POLICY_CANCEL) {

                  // Find an event handling thread for this type of event (if
                  // one exists).
                  std::map<AsgardEvent,boost::thread*>::iterator threadItr;
                  threadItr = asgardEventToThread.find(eventCode);

                  // If one exists, 
                  if (threadItr != asgardEventToThread.end()) {

                     // Then check to see if it's still running.  A thread
                     // which fails to join in 0ms is considered to be still
                     // running.  This check feels a bit kludgey to me, but
                     // Stack Overflow assures me that this is the way to do
                     // it.
                     boost::thread* thread = threadItr->second;
                     if (thread->timed_join(boost::posix_time::milliseconds(0)) == false) {

                        // Don't start a new thread if it's still running.
                        break;

                     }
                  }
               }

            }

            // Start an Event Handling Thread.
            boost::thread* eventHandlingThread = new boost::thread(
               boost::bind(&EventHandler::handle, eh, event)
            );


            // Post-Event Handling Thread Start Activities for Asgard Events.
            if (event.type == SDL_USEREVENT) {

               // Get the Asgard Event Type and Concurrency Policy.
               AsgardEvent eventCode = (AsgardEvent)event.user.code;
               ConcurrencyPolicy* policy = (ConcurrencyPolicy*)event.user.data2;

               // For the CANCEL policy we:
               // Record the Event Type and it's thread object in a special map
               // so that we know about it later on if another event tries to
               // start.
               if (*policy == CONCURRENCY_POLICY_CANCEL) {
                  this->asgardEventToThread[eventCode] = eventHandlingThread;
               }

            }

            }

            break;
         default:
            break;
      }
   }

}

/* getMode - Return the current mode of operation. */
AsgardMode Asgard::getMode() {
   return this->mode;
}

/* getEventHandler - Based on the current mode of operation, return the
 * EventHandler which should be accepting events. Return NULL if in a non-event
 * handling mode of operation. */
EventHandler* Asgard::getEventHandler() {
   if (this->mode == ASGARDMODE_MAP) {
      return Map::getInstance();
   } else {
      return NULL;
   }
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

   // Initialize Asgard's Python Interface.
   InitAsgardPython();
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

   // Activate the View Thread.
   boost::thread viewThread(&Asgard::view, this);

   // Activate the Controller Thread.
   boost::thread contThread(&Asgard::controller, this);

   // Wait for them to both to end.
   viewThread.join();
   contThread.join();
}


