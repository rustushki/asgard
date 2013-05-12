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
#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Drawable.h"
#include "Screen.h"
#include "Asgard.h"

class Layer;

class GraphicsEngine {
   public:
      GraphicsEngine();
      ~GraphicsEngine();

      static GraphicsEngine* getInstance();

      // Screen initiates it's updating loop
      void play();

      static void obtainLock();
      static void releaseLock();

      void displayDrawable(Drawable* d, std::string layerName, int x, int y);
      void translateDrawablesByOffset(std::vector<Drawable*> drawables, int x, int y);

      Layer* getLayerOfDrawable(Drawable* drawable);

   private:
      static GraphicsEngine* instance;
      static boost::shared_mutex updateLock;

      void sleep(long delay);
};

#endif//GRAPHICSENGINE_H
