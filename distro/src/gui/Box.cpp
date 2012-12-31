#include "Box.h"

Box::Box() {

}

Box::~Box() {

}

/* ------------------------------------------------------------------------------
 * setPosition - Set the top left corner of the box.  The coordinate provided
 * should be a screen coordinate.
 */
void Box::setPosition(Coordinate pos) {
   this->pos = pos;
   this->refresh();
}

/* ------------------------------------------------------------------------------
 * setDimension - Set the width and height of the box.
 */
void Box::setDimension(uint width, uint height) {
   this->width = width;
   this->height = height;
   this->refresh();
}

/* ------------------------------------------------------------------------------
 * getPosition - Return the coordinate of the top left corner of the box.
 * This is a screen coordinate.
 */
Coordinate Box::getPosition() const {
   return this->pos;
}

/* ------------------------------------------------------------------------------
 * getHeight - Get the Height of the Box.
 */
uint Box::getHeight() const {
   return this->height;
}

/* ------------------------------------------------------------------------------
 * getWidth - Get the Width of the Box.
 */
uint Box::getWidth() const {
   return this->width;
}


/* ------------------------------------------------------------------------------
 * show - Display the Box instance on the GUI Layer of the GraphicsEngine.
 */
void Box::show() const {

}

/* ------------------------------------------------------------------------------
 * hide - Hide this Box instance and do not show it on the GUI Layer of the
 * GraphicsEngine any longer.
 */
void Box::hide() const {

}

/* ------------------------------------------------------------------------------
 * refresh - Update all graphical elements associated with this Box instance.
 */
void Box::refresh() {
   
}
