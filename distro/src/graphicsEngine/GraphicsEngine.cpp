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

#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::instance = NULL;
boost::shared_mutex GraphicsEngine::updateLock;

extern boost::mutex gate;

GraphicsEngine::GraphicsEngine() {
   LOG(INFO) << "GraphicsEngine starting ...";

   // Ensure Screen has been initialized.
   Screen::getInstance();
}

GraphicsEngine::~GraphicsEngine() {

}

GraphicsEngine* GraphicsEngine::getInstance() {
   if(instance == NULL) instance = new GraphicsEngine();
   return instance;
}

void GraphicsEngine::play() {
   int time = 0;
   Screen* s = Screen::getInstance();

   while(true) {

      // Handle the "Quitting" Mode of Operation.
      if (Asgard::getInstance()->getMode() == ASGARDMODE_QUITTING) {
         // Exit thread.
         return;
      }

      time = SDL_GetTicks();

      // Wait for write access to layers.  Once obtained, update them.
      GraphicsEngine::obtainLock();
      s->prepare();
      GraphicsEngine::releaseLock();

      s->flip();
      time = SDL_GetTicks() - time;

      // A delay of <= 0 causes this thread to never wake up
      int delay = (1000/Screen::FPS)-time;
      if (delay <= 0) {
         delay = 1;
      }

      // Unlock the Controller Gate
      Asgard::getInstance()->gate.notify_one();

      boost::this_thread::sleep(boost::posix_time::milliseconds(delay));
   }
}

// Wait for write access to the screen/layers.
void GraphicsEngine::obtainLock() {
   return GraphicsEngine::updateLock.lock_shared();
}

void GraphicsEngine::releaseLock() {
   GraphicsEngine::updateLock.unlock_shared();
}

void GraphicsEngine::displayDrawable(Drawable* d, std::string layerName, int x, int y) {
   LOG(INFO) << "Displaying Drawable";

   Screen* s = Screen::getInstance();
   Layer * l = s->getLayer(layerName);

   d->move(x, y);

   // TODO: parameterize whether to play or not.
   d->play();

   // TODO: parameterize stack location on layer
   // Always on the top?
   if (l != NULL) {
      l->insertDrawableTop(d);
   }
}

void GraphicsEngine::translateDrawablesByOffset(std::vector<std::string>* drawableNames, int xOffset, int yOffset) {
   LOG(INFO) << "Translating Drawables By an Offset";

   Screen* s = Screen::getInstance();

   std::vector<std::string>::iterator itr;
   for (itr = drawableNames->begin(); itr != drawableNames->end(); itr++) {
      std::string drawableName = *itr;
      LOG(INFO) << "Can we find " << drawableName << "?";
      Drawable* d = s->getDrawableByName(drawableName);
      if (d != NULL) {
         LOG(INFO) << "Found it.  Moving by offset.";
         d->moveByOffset(xOffset, yOffset);
      }
   }
}

void GraphicsEngine::unloadDrawable(std::string drawableInstanceName) {
   LOG(INFO) << "Unloading Drawable.";

   Screen* s = Screen::getInstance();

   Drawable* d = s->getDrawableByName(drawableInstanceName);

   if (d != NULL) {
	   LOG(INFO) << "Successfully found drawable to unload.";
      d->unload();
   } else {
	   LOG(INFO) << "Unable to find Drawable for unloading.";
   }
}

