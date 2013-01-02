#include "Animation.h"
#include "SpriteSheetCache.h"
#include "Screen.h"

Animation::Animation(std::string filename, uint width, uint height, uint sps, uint ssRows, uint ssCols)
{
   SpriteSheetCache* ssCache = SpriteSheetCache::getInstance();
   this->spriteSheet = ssCache->retrieve(filename);
   this->init(width, height, sps, ssRows, ssCols);
}

Animation::Animation(SDL_Surface* surf, uint width, uint height, uint sps, uint ssRows, uint ssCols)
{
   this->spriteSheet = surf;
   this->init(width, height, sps, ssRows, ssCols);
}

Animation::Animation(SDL_Surface* surf)
{
   this->spriteSheet = surf;
   this->init(surf->w, surf->h, 1, 1, 1);
}

void Animation::init(uint width, uint height, uint sps, uint ssRows, uint ssCols) {
   this->width  = width;
   this->height = height;
   this->currentStill = 0;
   this->sps = sps;
   this->status = ANIMATIONSTATE_IDLE;
   this->frameCounter = 0;
   this->ssRows = ssRows;
   this->ssCols = ssCols;
}

void Animation::setSPS(uint sps)
{
   this->sps = sps;
}

uint Animation::getSPS()
{
   return this->sps;
}

AnimationState Animation::getStatus()
{
   return this->status;
}

void Animation::advance()
{
   if (this->currentStill < this->getStillCount()-1)
      this->currentStill++;
   else
      this->currentStill = 0;
}

void Animation::incFrameCounter()
{
   if (this->frameCounter < Screen::FPS/this->sps)
      this->frameCounter++;
   else
      this->frameCounter = 0;
}

bool Animation::needsUpdate()
{
   // Animations with only 1 still do not need to update ever.
   if (this->getStillCount() == 1)
      return false;

   return (this->frameCounter == (Screen::FPS/this->sps));
}

uint Animation::getWidth()
{
   return this->width;
}

uint Animation::getHeight()
{
   return this->height;
}

void Animation::updateRect(SDL_Rect r, uint offsetX, uint offsetY)
{
   uint stillX; 
   uint stillY;

   // Compute the slot X,Y for the still.
   // An animation with 1 still is a special case.
   if (this->getStillCount() == 1)
   {
      stillX = 0;
      stillY = 0;
   }
   else
   {
      stillX = currentStill%(this->ssCols);
      stillY = currentStill/(this->ssCols);
   }

   // Compute the sprite sheet clip, factor in the provided xy offset.
   SDL_Rect stillClip;
   stillClip.x = stillX*this->width + offsetX;
   stillClip.y = stillY*this->height + offsetY;
   stillClip.w = r.w;
   stillClip.h = r.h;

   // Do a blit to the Screen.
   RectBlitter* rb = RectBlitter::getInstance();
   rb->blit(r, this->spriteSheet, stillClip);
}

/* -----------------------------------------------------------------------------
 * getStillCount - Return an unsigned int which is defined as the number of
 * columns times the number of rows in the spritesheet.  This is equal to the
 * total number of stills available for the animation.
 */
uint Animation::getStillCount() {

	// Rows * Cols == Still Count.
	return this->ssRows * this->ssCols;

}
