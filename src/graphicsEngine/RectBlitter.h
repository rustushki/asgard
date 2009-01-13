#ifndef RECT_BLITTER_H
#define RECT_BLITTER_H
#include <SDL/SDL.h>
class Animation;

class RectBlitter
{
   public:
      static RectBlitter* getInstance();

   private:
      // Clip from the provided spritesheet, blit to the Screen.
      void blit(SDL_Rect rect, SDL_Surface* spriteSheet, SDL_Rect clip);

      RectBlitter();
      static RectBlitter* instance;

   friend class Animation;
};
#endif//RECT_BLITTER_H
