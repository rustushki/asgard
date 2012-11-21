#ifndef BOX_H
#define BOX_H

#include "externals.h"
#include "Coordinate.h"
#include "Drawable.h"

class Box {

public:
	~Box();

	// Setters and Getters for positional and dimensional values.
	void setPosition(Coordinate pos);
	void setDimension(uint width, uint height);
	Coordinate getPosition() const;
	uint getHeight() const;
	uint getWidth() const;

protected:
	Box();

private:

	// Position and Dimension Details
	uint height;
	uint width;
	Coordinate pos;

	// Drawable for this box.
	Drawable* box;

};

#endif//BOX_H
