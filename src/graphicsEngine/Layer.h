#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include "GraphicsEngine.h"
#include "LayerState.h"
class Drawable;

class Layer
{
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
      void insertDrawable(Drawable* drawable, int zIndex);
      void insertDrawableTop(Drawable* drawable);
      void insertDrawableBottom(Drawable* drawable);
      bool removeDrawable(std::string name);

      // Blit all data from this layer that intersects with the provided rect.
      void updateRect(SDL_Rect r);

      // Do a data update on the Layer.
      void update();
};

#endif//LAYER_H
