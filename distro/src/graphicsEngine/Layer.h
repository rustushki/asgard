#ifndef LAYER_H
#define LAYER_H

#include "externals.h"
#include "GraphicsEngine.h"
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
      void removeDrawable(std::string name);
      Drawable* getDrawableByName(std::string name) const;
      Drawable* getDrawableByCommonName(std::string name) const;

      void stackAonB(std::string drawableAName, std::string drawableBName);

      // Blit all data from this layer that intersects with the provided rect.
      void updateRect(SDL_Rect r);

      // Do a data update on the Layer.
      void update();

};

#endif//LAYER_H
