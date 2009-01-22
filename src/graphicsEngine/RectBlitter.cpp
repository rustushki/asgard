#include "RectBlitter.h"
#include "Screen.h"

RectBlitter* RectBlitter::instance = NULL;

RectBlitter::RectBlitter()
{

}

RectBlitter* RectBlitter::getInstance()
{
   if (RectBlitter::instance == NULL)
      RectBlitter::instance = new RectBlitter();

   return RectBlitter::instance;
}

void RectBlitter::blit(SDL_Rect r, SDL_Surface* spriteSheet, SDL_Rect clip)
{
   Screen* s = Screen::getInstance();

   SDL_BlitSurface(spriteSheet, &clip, s->nextFrame, &r);
}
