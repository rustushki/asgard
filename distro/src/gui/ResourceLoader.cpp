#include "ResourceLoader.h"

SDL_Surface* ResourceLoader::LoadSDLSurface(std::string elementPath) {

   // Otherwise, read and create from hard disk.
   SDL_Surface* surface = NULL;
   SDL_Surface* surfaceRaw = NULL;

   // Search for spritesheets in the RES directory.
   std::string path(RES);
   path.append(elementPath);

   // TODO: File Exists?

   // Handle PNG transparency.
   SDL_RWops *rwop;
   rwop = SDL_RWFromFile(path.c_str(), "rb");
   bool alpha = IMG_isPNG(rwop);

   surfaceRaw = IMG_Load(path.c_str());

   if (surfaceRaw != NULL)
   {
      if (alpha) {
         surface = SDL_DisplayFormatAlpha(surfaceRaw);
         SDL_FreeSurface(surfaceRaw);
      } else {
         surface = SDL_DisplayFormat(surfaceRaw);
         SDL_FreeSurface(surfaceRaw);

         // Hot pink transparency color.
         uint colorkey = SDL_MapRGB(surface->format, 0xff, 0, 0xff);
         SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
      }
   }

   return surface;

}

