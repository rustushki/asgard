#include "Coordinate.h"

Coordinate::Coordinate(int x0, int y0)
{
	x = x0;
	y = y0;
}

int Coordinate::getX()
{
	return x;
}

int Coordinate::getY()
{
	return y;
}

void Coordinate::setX(int x0)
{
	x = x0;
}

void Coordinate::setY(int y0)
{
	y = y0;
}

