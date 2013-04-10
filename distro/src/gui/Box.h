#ifndef BOX_H
#define BOX_H

#include "externals.h"
#include "Coordinate.h"
#include "Drawable.h"
#include "GraphicsEngine.h"
#include "Theme.h"

class Box {

public:
	~Box();

	// Setters and Getters for positional and dimensional values.
	void setPosition(Coordinate pos);
	void setDimension(uint width, uint height);
	Coordinate getPosition() const;
	uint getHeight() const;
	uint getWidth() const;

	void show() const;
	void hide() const;
   void unload() const;
	void refresh();

protected:
	Box();

   void twoDimTile    (SDL_Surface* surf, Uint16 x, Uint16 y, Uint16 w, Uint16 h);
   void horzLinearTile(SDL_Surface* surf, Uint16 x, Uint16 y, Uint16 w);
   void vertLinearTile(SDL_Surface* surf, Uint16 x, Uint16 y, Uint16 h);
   void singBlit      (SDL_Surface* surf, Uint16 x, Uint16 y);

   virtual void buildSurface();

   // Construct the surface for the Drawable here.
   SDL_Surface* tempSurf;

private:

	// Position and Dimension Details
	uint height;
	uint width;
	Coordinate pos;

	// Drawable for this box.
	Drawable* box;

};

#endif//BOX_H
