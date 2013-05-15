#include "ResourceLoader.h"

ResourceLoader* ResourceLoader::instance = NULL;

ResourceLoader::ResourceLoader() {
}

ResourceLoader* ResourceLoader::GetInstance() {
   if (ResourceLoader::instance == NULL) {
      ResourceLoader::instance = new ResourceLoader();
   }

   return ResourceLoader::instance;
}

SDL_Surface* ResourceLoader::loadSDLSurface(std::string elementPath) {

   // Get an iterator into the surfCache.
   std::map<std::string, SDL_Surface*>::iterator iter = surfCache.begin();

   // Return the spritesheet if can be found in the cache
   iter = surfCache.find(elementPath);
   if (iter != surfCache.end()) {
      return iter->second;
   }

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

   surfCache[elementPath] = surface;

   return surface;

}

/* ------------------------------------------------------------------------------
 * getFont - Load a font for usage.
 *
 * TODO:
 * Optimize this by keeping the font loaded in memory.
 */
TTF_Font* ResourceLoader::getFont(std::string fontFn, Uint16 pointSize) {

   std::string key = fontFn + std::to_string(pointSize);

   // Get an iterator into the surfCache.
   std::map<std::string, TTF_Font*>::iterator iter = ttfCache.begin();

   // Return the spritesheet if can be found in the cache
   iter = ttfCache.find(key);
   if (iter != ttfCache.end()) {
      return iter->second;
   }

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

   ttfCache[key] = font;

   // Return the font.
   return font;
}
