#include "SpriteSheetCache.h"
#include "consts.h"

SpriteSheetCache* SpriteSheetCache::instance = NULL;

SpriteSheetCache::SpriteSheetCache() {

}

SpriteSheetCache::~SpriteSheetCache() {
   // Free all SDL Surfaces in the Cache.
   CacheMap::iterator iter = this->cache.begin();
   while (iter != this->cache.end()) {
      SDL_FreeSurface(iter->second);
   }
}

SpriteSheetCache* SpriteSheetCache::getInstance() {
   if (SpriteSheetCache::instance == NULL) {
      SpriteSheetCache::instance = new SpriteSheetCache();
   }
   return SpriteSheetCache::instance;
}

SDL_Surface* SpriteSheetCache::retrieve(std::string name) {

   // Get CacheMap iterator.
   CacheMap::iterator iter = this->cache.begin();

   // Return the spritesheet can be found in the cache
   iter = this->cache.find(name);
   if (iter != this->cache.end()) {
      return iter->second;
   }

   // Otherwise, read and create from hard disk.
   SDL_Surface* spriteSheet = NULL;
   SDL_Surface* spriteSheetRaw = NULL;

   // Search for spritesheets in the RES directory.
   std::string path(RES);
   path.append("spritesheet/");
   path.append(name);

   // TODO: File Exists?

   // Handle PNG transparency.
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

   return spriteSheet;
}
