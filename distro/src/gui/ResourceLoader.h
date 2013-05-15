#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "consts.h"
#include "externals.h"

class ResourceLoader {

public:
   static ResourceLoader* GetInstance();

   SDL_Surface* loadSDLSurface(std::string path);
   TTF_Font* getFont(std::string fontFn, Uint16 pointSize);

   ~ResourceLoader();

private:

   static ResourceLoader* instance;
   ResourceLoader();
   std::map<std::string, SDL_Surface*> surfCache;
   std::map<std::string, TTF_Font*> ttfCache;

};

#endif//RESOURCELOADER_H
