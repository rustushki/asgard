#ifndef BOX_H
#define BOX_H

#include "Coordinate.h"

class Drawable;
class ScreenPoint;

class Box {

public:
	~Box();

	// Setters and Getters for positional and dimensional values.
	void setPosition(Coordinate<ScreenPoint> pos);
	void setDimension(uint width, uint height);
	Coordinate<ScreenPoint> getPosition() const;
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

   std::shared_ptr<SDL_Surface> getTempSurf();

private:

	// Position and Dimension Details
	uint height;
	uint width;
	Coordinate<ScreenPoint> pos;

	// Drawable for this box.
	Drawable* box;

   // Construct the surface for the Drawable here.
   std::shared_ptr<SDL_Surface> tempSurf;

};

#endif//BOX_H
