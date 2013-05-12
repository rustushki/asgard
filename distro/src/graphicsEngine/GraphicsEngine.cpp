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
   Uint32 time = 0;
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
      long delay = (1000/Screen::FPS)-time;
      if (delay <= 0) {
         delay = 1;
      }

      // Unlock the Controller Gate
      Asgard::getInstance()->gate.notify_one();

      sleep(delay);
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

void GraphicsEngine::translateDrawablesByOffset(std::vector<Drawable*> drawables, int xOffset, int yOffset) {
   LOG(INFO) << "Translating Drawables By an Offset";

   std::vector<Drawable*>::iterator itr;
   for (itr = drawables.begin(); itr != drawables.end(); itr++) {
      (*itr)->moveByOffset(xOffset, yOffset);
   }
}

/* ------------------------------------------------------------------------------
 * getLayerOfDrawable - Return the Layer of a provided Drawable
 *
 * Returns NULL if no Layer.
 */
Layer* GraphicsEngine::getLayerOfDrawable(Drawable* drawable) {
   return Screen::getInstance()->getLayerOfDrawable(drawable);
}

void GraphicsEngine::sleep(long delay) {
#if BOOST_VERSION >= 105000
   boost::this_thread::sleep_for(boost::chrono::milliseconds(delay));
#else
   boost::this_thread::sleep(boost::posix_time::milliseconds(delay));
#endif
}
