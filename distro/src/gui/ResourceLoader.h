#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "consts.h"
#include "externals.h"

class ResourceLoader {

public:
   static SDL_Surface* LoadSDLSurface(std::string path);

};

#endif//RESOURCELOADER_H
