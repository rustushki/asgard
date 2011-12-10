/*****************************************************************************
 * Copyright (c) 2009 Russ Adams, Sean Eubanks, Asgard Contributors
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

struct Message;

class GraphicsEngine
{
   public:
      GraphicsEngine();
      ~GraphicsEngine();

      static GraphicsEngine* getInstance();

      // Screen initiates it's updating loop
      void play();

      static void obtainLock();
      static void releaseLock();

   private:
      static GraphicsEngine* instance;
      //void handleDisplayDrawable(Message* message);
      //void handleTranslateDrawablesByOffset(Message* message);
      //void handleUnloadDrawable(Message* message);
      static boost::shared_mutex updateLock;
      bool eventHandler(SDL_Event& event);
};

#endif // GRAPHICSENGINE_H
