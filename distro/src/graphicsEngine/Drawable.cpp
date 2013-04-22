/*****************************************************************************
 * Copyright (c) 2013 Russ Adams, Sean Eubanks, Asgard Contributors
 * This file is part of Asgard.
 * 
 * Asgard is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asgard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with Asgard; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/
#include "Screen.h"
#include "Drawable.h"

unsigned int Drawable::nextUniqueNumber = 0;

Drawable::Drawable(std::string name) {
   this->name = name;
   this->moved = false;
   this->swapped = false;
   this->newAnimation = "";
   this->x = 0;
   this->y = 0;
   this->newX = 0;
   this->newY = 0;
   this->hidden = false;
   this->hasBeenHidden = true;
   this->toBeRemoved = false;

   // Set the Unique Instance Name
   char uniq[9];
   sprintf(uniq, "%08x", nextUniqueNumber);
   this->instanceName = this->name + uniq;
   Drawable::nextUniqueNumber++;
}

Drawable::~Drawable() {
}

/**
 * getName()
 *
 * Returns the generic name of the drawable.  This is effectively the "type" or
 * "class" of drawable.
 *
 * @return std::string - <drawableName> (i.e. "tree")
 */
std::string Drawable::getName() {
   return this->name;
}

DrawableState Drawable::getStatus() {
   return this->status;
}

void Drawable::setX(int x) {
   this->x = x;
}

void Drawable::setY(int y) {
   this->y = y;
}

int Drawable::getX() {
   return this->x;
}

int Drawable::getY() {
   return this->y;
}

/* -----------------------------------------------------------------------------
 * getHeight - Return the height of the current animation of the Drawable.
 */
uint Drawable::getHeight() const {
   // Use std::map::find() so that this function may be declared as const.
   Animation* ca = this->animation.find(this->currentAnimation)->second;
   return ca->getHeight();
}

/* -----------------------------------------------------------------------------
 * getWidth - Return the width of the current animation of the Drawable.
 */
uint Drawable::getWidth() const {
   // Use std::map::find() so that this function may be declared as const.
   Animation* ca = this->animation.find(this->currentAnimation)->second;
   return ca->getWidth();
}

void Drawable::addAnimation(Animation* animation, std::string name) {
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->animation[name] = animation;

   // Set the current animation if there wasn't one set before.
   if (this->animation.size() == 1) {
      this->currentAnimation = name;
      if (this->newAnimation == "")
         this->newAnimation = name;
   }
}

bool Drawable::removeAnimation(std::string name) {
   if (this->animation.erase(name) >= 1)
      return true;
   return false;
}

bool Drawable::swapAnimation(std::string name) {
   if (this->animation.find(name) != this->animation.end()) {
      this->swapped = true;
      this->newAnimation = name;
      return true;
   }
   return false;
}

std::string Drawable::getCurrentAnimation() {
   return this->currentAnimation;
}

bool Drawable::needsUpdate() {
   Animation* ca = this->animation[this->currentAnimation];

   // Return true when the Drawable has moved OR the animation has changed OR
   // the animation is ready to be updated.
   bool needsUpdate = false;
   needsUpdate |= this->moved;
   needsUpdate |= this->swapped;
   needsUpdate |= ca->needsUpdate();
   needsUpdate &= this->status == DRAWABLESTATE_PLAYING;
   return needsUpdate;
}

void Drawable::move(int newX, int newY) {
   /*
   LOG(INFO) << "instance = " << this->getInstanceName();
   LOG(INFO) << "oldX = " << this->x;
   LOG(INFO) << "oldY = " << this->y;
   LOG(INFO) << "newX = " << newX;
   LOG(INFO) << "newY = " << newY;
   */

   // Hold the new x,y pair until we're preparing the next Screen frame.
   this->newX = newX;
   this->newY = newY;
   this->moved = true;
}

void Drawable::moveByOffset(int offX, int offY) {
   this->move((int)this->x + offX, (int)this->y + offY);
}

void Drawable::play() {
   this->status = DRAWABLESTATE_PLAYING;
}

void Drawable::stop() {
   this->status = DRAWABLESTATE_IDLE;
}

void Drawable::hide() {
   
   // Prevents animation from being blitted to screen.
   this->hidden = true;

   // Ensure that the visible portion of the drawable is hidden exactly once.
   // No need to do it more than once.
   this->hasBeenHidden = false;
}

void Drawable::show() {
   this->hidden = false;
}

void Drawable::unload() {
   this->hide();
   this->toBeRemoved = true;
}

SDL_Rect Drawable::getIntersectingRect(SDL_Rect r) {
   Animation* ca = this->animation[this->currentAnimation];

   int l1, r1, t1, b1;
   int l2, r2, t2, b2;

   // Compute the sides of the provided rect.
   l1 = r.x;
   r1 = r.x+r.w;
   t1 = r.y;
   b1 = r.y+r.h;
   
   // Compute the sides of the current Animation.
   l2 = this->x;
   r2 = this->x+ca->getWidth();
   t2 = this->y;
   b2 = this->y+ca->getHeight();

   // Compute the intersecting rectangle.
   SDL_Rect i;
   i.w = ((double)(std::min(r1,r2) - std::max(l1,l2)));
   i.h = ((double)(std::min(b1,b2) - std::max(t1,t2)));
   i.x = std::max(l1,l2);
   i.y = std::max(t1,t2);

   if (i.w < 0) {
      i.w = 0;
   }

   if (i.h < 0) {
      i.h = 0;
   }

   return i;
}

void Drawable::updateRect(SDL_Rect r) {

   // Do not have animation blit itself if the Drawable is hidden.
   if (this->hidden) {
      return;
   }

   int l1, r1, b1, t1;
   int l2, r2, b2, t2;

   Animation* ca = this->animation[this->currentAnimation];

   // Compute the sides of the animation.
   l1 = this->x;
   r1 = this->x+ca->getWidth();
   t1 = this->y;
   b1 = this->y+ca->getHeight();
   
   // Compute the sides of the provided rect.
   l2 = r.x;
   r2 = r.x+r.w;
   t2 = r.y;
   b2 = r.y+r.h;

   // Does the current animation intersect with the provided rect?  If so,
   // update the animation.
   if (!(l1 > r2 || r1 < l2 || t1 > b2 || b1 < t2))
   {
      // Get the intersecting rect.
      SDL_Rect v = this->getIntersectingRect(r);

      // Update the intersecting rect.
      int offsetX = (double)(v.x - this->x);
      int offsetY = (double)(v.y - this->y);
      ca->updateRect(v,offsetX,offsetY);
   }
}

void Drawable::doMove() {
   if (this->x != this->newX || this->y != this->newY)
   {
      SDL_Rect r = this->getRect();

      this->x = this->newX;
      this->y = this->newY;

      Screen* s = Screen::getInstance();
      s->updateRect(r);
   }
}

void Drawable::doSwap() {
   if (this->currentAnimation != this->newAnimation)
   {
      SDL_Rect r = this->getRect();

      this->currentAnimation = this->newAnimation;

      Screen* s = Screen::getInstance();
      s->updateRect(r);
   }
}

void Drawable::doAnim() {
   Animation* ca = this->animation[this->currentAnimation];
   ca->incFrameCounter();

   if (this->needsUpdate())
   {
      if (ca->needsUpdate())
         ca->advance();

      SDL_Rect r = this->getRect();

      this->moved = false;
      this->swapped = false;

      Screen* s = Screen::getInstance();
      s->updateRect(r);
   }
}

void Drawable::doHide() {
   if (this->hidden && !this->hasBeenHidden) {

      // Notify screen that this Drawable's visible rect must be updated.
      // (though the Drawable itself be hidden)  When Drawable::updateRect() is
      // called, the Drawable::hidden flag will be 'true' causing the routine
      // to not draw the drawable on the screen.  Layers above and below may,
      // however, blit animations within the rect.  This effectively hides the
      // Drawable.
      SDL_Rect r = this->getRect();
      Screen* s = Screen::getInstance();
      s->updateRect(r);

      // Prevent Drawable::doHide() from hiding the Drawable again.
      this->hasBeenHidden = true;
   }
}

SDL_Rect Drawable::getRect() {
   Animation* ca = this->animation[this->currentAnimation];
   SDL_Rect r;
   r.x = this->x;
   r.y = this->y;
   r.w = ca->getWidth();
   r.h = ca->getHeight();
   return r;
}
