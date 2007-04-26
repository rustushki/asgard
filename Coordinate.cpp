#include "Coordinate.h"

Coordinate::Coordinate()
{
   //Initialize to zero
   this->x = 0;
   this->y = 0;
}

Coordinate::Coordinate(int x, int y)
{
   this->x = x;
	this->y = y;
}

int Coordinate::getX()
{
	return this->x;
}

int Coordinate::getY()
{
	return this->y;
}

void Coordinate::setX(int x)
{
	this->x = x;
}

void Coordinate::setY(int y)
{
	this->y = y;
}

