#ifndef SPRITESHEETCACHE_H
#define SPRITESHEETCACHE_H
#include "externals.h"

class SpriteSheetCache {

public:
	static SpriteSheetCache* getInstance();
	SpriteSheetCache();
	~SpriteSheetCache();
	SDL_Surface* retrieve(std::string name);

private:
	static SpriteSheetCache* instance;

	typedef std::map<std::string, SDL_Surface*> CacheMap;
	CacheMap cache;

};

#endif//SPRITESHEETCACHE_H
