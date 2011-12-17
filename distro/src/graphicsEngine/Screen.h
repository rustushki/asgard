#ifndef SCREEN_H
#define SCREEN_H

#include "externals.h"
#include "Layer.h"
#include "ScreenState.h"

class Layer;

class Screen
{
   public:
      static Screen* getInstance();
      ~Screen();

      // Update the display with the next frame.
      void flip();

      // Prepare the next frame.
      void prepare();

      ScreenState getStatus() const;
      
      // Layers are displayed in stacking order.
      // Methods for adding and removing Layers.
      void insertLayer(Layer* newLayer, unsigned int position);
      void removeLayer(std::string name);
      void appendLayer(Layer* newLayer);
      void pushLayer(Layer* newLayer);
      Layer* getLayer(std::string name) const;

      Drawable* getDrawableByName(std::string name);


      // Do a blit onto the Screen from all layers that intersect with provided
      // rect.
      void updateRect(SDL_Rect r);

      // Frames Per Second.
      static const uint FPS    = 25;

      // Screen Width
      static const uint WIDTH  = 800;

      // Screen Height
      static const uint HEIGHT = 600;

   private:
      Screen();

      // Singleton instance.
      static Screen* instance;

      // Initialize self by adding background stage.
      void init();

      // Frame to be displayed next.
      SDL_Surface* nextFrame;

      // Layers to be drawn in stacking order.
      std::vector<Layer*> layer;

      // Descriptor for Screen's current state.
      ScreenState status;

      // List of rects to update on the display.
      std::vector<SDL_Rect> rectsToUpdate;

   // RectBlitter, a singleton, is given access to Screen.
   friend class RectBlitter;
};
#endif//SCREEN_H
