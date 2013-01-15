#include "ResourceLoader.h"
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

   return ResourceLoader::LoadSDLSurface(std::string("spritesheet/"+name));
}
