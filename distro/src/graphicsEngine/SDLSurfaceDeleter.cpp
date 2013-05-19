#include "externals.h"
#include "SDLSurfaceDeleter.h"

SDLSurfaceDeleter::SDLSurfaceDeleter() {};

SDLSurfaceDeleter::SDLSurfaceDeleter(const SDLSurfaceDeleter& other){
}

SDLSurfaceDeleter::SDLSurfaceDeleter(SDLSurfaceDeleter& other){
}

SDLSurfaceDeleter::SDLSurfaceDeleter(SDLSurfaceDeleter&& other){
}

void SDLSurfaceDeleter::operator() (SDL_Surface* p) const {

   SDL_FreeSurface(p);

};
