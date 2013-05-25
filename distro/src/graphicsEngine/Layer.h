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
#ifndef LAYER_H
#define LAYER_H

#include "externals.h"
#include "LayerState.h"

class Drawable;

class Layer {

   private:
      std::vector<Drawable*> drawable;
      std::string name;
      LayerState status;

   public:
      Layer(std::string name);
      ~Layer();

      std::string getName();
      LayerState getStatus();

      // Methods for adding and removing Drawables.
      // Drawables are stored in the layer in stacking order.
      void insertDrawable(Drawable* drawable, unsigned int zIndex);
      void insertDrawableTop(Drawable* drawable);
      void insertDrawableBottom(Drawable* drawable);
      void removeDrawable(Drawable* drawable);

      void stackAonB(Drawable* a, Drawable* b);

      bool isDrawablePresent(Drawable* d);

      // Blit all data from this layer that intersects with the provided rect.
      void updateRect(SDL_Rect r);

      // Do a data update on the Layer.
      void update();

};

#endif//LAYER_H
