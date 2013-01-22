#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "consts.h"
#include "externals.h"

class ResourceLoader {

public:
   static SDL_Surface* LoadSDLSurface(std::string path);
   static TTF_Font* GetFont(std::string fontFn, Uint16 pointSize);

};

#endif//RESOURCELOADER_H
