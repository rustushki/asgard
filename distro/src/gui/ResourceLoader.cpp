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

/* ------------------------------------------------------------------------------
 * GetFont - Load a font for usage.
 *
 * TODO:
 * Optimize this by keeping the font loaded in memory.
 */
TTF_Font* ResourceLoader::GetFont(std::string fontFn, Uint16 pointSize) {

   // Build path to the Font Resource.
   std::string path(RES);
   path.append("font/");
   path.append(fontFn);

   // Load Font
   TTF_Font* font = TTF_OpenFont(path.c_str(), pointSize);

   TTF_SetFontHinting(font, TTF_HINTING_NORMAL);


   // Handle Font Load Error.
   if (!font) {
      LOG(INFO) << "Failure to load font";
      LOG(INFO) << "Path:" << path;
      LOG(ERROR) << TTF_GetError();
      exit(1);
   }

   // Return the font.
   return font;
}
