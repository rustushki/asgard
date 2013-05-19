#ifndef SDLSURFACEDELETER_H
#define SDLSURFACEDELETER_H

struct SDL_Surface;

struct SDLSurfaceDeleter{

   SDLSurfaceDeleter();

   SDLSurfaceDeleter(const SDLSurfaceDeleter& other);

   SDLSurfaceDeleter(SDLSurfaceDeleter& other);

   SDLSurfaceDeleter(SDLSurfaceDeleter&& other);

   void operator () (SDL_Surface* p) const;
};

#endif//SDLSURFACEDELETER_H
