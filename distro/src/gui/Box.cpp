#include "Box.h"

Box::Box() {

}

Box::~Box() {

}

void Box::setPosition(Coordinate pos) {
   this->pos = pos;
}

void Box::setDimension(uint width, uint height) {
   this->width = width;
   this->height = height;
}

Coordinate Box::getPosition() const {
   return this->pos;
}

uint Box::getHeight() const {
   return this->height;
}

uint Box::getWidth() const {
   return this->width;
}
