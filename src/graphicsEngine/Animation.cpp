#include "Animation.h"
#include "Screen.h"
#include "consts.h"

Animation::Animation(std::string filename, uint width, uint height, uint stillCount, uint sps, uint ssRows, uint ssCols)
{
   SDL_Surface* spriteSheetRaw = NULL;
   SDL_Surface* spriteSheet = NULL;

   // Search for spritesheets in the RES directory.
   std::string path(RES);
   path.append("spritesheet/");
   path.append(filename);

   // TODO: File Exists?

   // Handle PNG transparancy.
   SDL_RWops *rwop;
   rwop=SDL_RWFromFile(path.c_str(), "rb");
   bool alpha = false;
   if (IMG_isPNG(rwop)) {
      alpha = true;
   }

   spriteSheetRaw = IMG_Load(path.c_str());

   if (spriteSheetRaw != NULL)
   {
      if (alpha) {
         spriteSheet = SDL_DisplayFormatAlpha(spriteSheetRaw);
         SDL_FreeSurface(spriteSheetRaw);
      } else {
         spriteSheet = SDL_DisplayFormat(spriteSheetRaw);
         SDL_FreeSurface(spriteSheetRaw);

         // Hot pink transparency color.
         uint colorkey = SDL_MapRGB(spriteSheet->format, 0xff, 0, 0xff);
         SDL_SetColorKey(spriteSheet, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
      }
   }

   this->spriteSheet = spriteSheet;
   this->width  = width;
   this->height = height;
   this->stillCount = stillCount;
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
   if (this->currentStill < this->stillCount-1)
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
   if (this->stillCount == 1)
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
   if (this->stillCount == 1)
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
