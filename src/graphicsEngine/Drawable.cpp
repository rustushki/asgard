#include <cmath>
#include "Screen.h"
#include "Drawable.h"

Drawable::Drawable(std::string name)
{
   this->name = name;
   this->moved = false;
   this->swapped = false;
   this->newAnimation = "";
   this->x = 0;
   this->y = 0;
   this->newX = 0;
   this->newY = 0;
}

std::string Drawable::getName()
{
   return this->name;
}

DrawableState Drawable::getStatus()
{
   return this->status;
}

void Drawable::addAnimation(Animation* animation, std::string name)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->animation[name] = animation;

   // Set the current animation if there wasn't one set before.
   if (this->animation.size() == 1)
   {
      this->currentAnimation = name;
      if (this->newAnimation == "")
         this->newAnimation = name;
   }
}

bool Drawable::removeAnimation(std::string name)
{
   if (this->animation.erase(name) >= 1)
      return true;
   return false;
}

bool Drawable::swapAnimation(std::string name)
{
   if (this->animation.find(name) != this->animation.end())
   {
      this->swapped = true;
      this->newAnimation = name;
      return true;
   }
   return false;
}

std::string Drawable::getCurrentAnimation()
{
   return this->currentAnimation;
}

bool Drawable::needsUpdate()
{
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

bool Drawable::move(uint newX, uint newY)
{
   // Hold the new x,y pair until we're preparing the next Screen frame.
   this->newX = newX;
   this->newY = newY;
   this->moved = true;
}

void Drawable::play()
{
   this->status = DRAWABLESTATE_PLAYING;
}

void Drawable::stop()
{
   this->status = DRAWABLESTATE_IDLE;
}

SDL_Rect Drawable::getIntersectingRect(SDL_Rect r)
{
   Animation* ca = this->animation[this->currentAnimation];

   uint l1, r1, t1, b1;
   uint l2, r2, t2, b2;

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
   i.w = std::abs((double)(std::min(r1,r2) - std::max(l1,l2)));
   i.h = std::abs((double)(std::min(b1,b2) - std::max(t1,t2)));
   i.x = std::max(l1,l2);
   i.y = std::max(t1,t2);

   return i;
}

void Drawable::updateRect(SDL_Rect r)
{
   uint l1, r1, b1, t1;
   uint l2, r2, b2, t2;

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
      r = this->getIntersectingRect(r);

      // Update the intersecting rect.
      uint offsetX = std::abs((double)(r.x - this->x));
      uint offsetY = std::abs((double)(r.y - this->y));
      ca->updateRect(r,offsetX,offsetY);
   }
}

void Drawable::doMove()
{
   if (this->x != this->newX || this->y != this->newY)
   {
      SDL_Rect r = this->getRect();

      this->x = this->newX;
      this->y = this->newY;

      Screen* s = Screen::getInstance();
      s->updateRect(r);
   }
}

void Drawable::doSwap()
{
   if (this->currentAnimation != this->newAnimation)
   {
      SDL_Rect r = this->getRect();

      this->currentAnimation = this->newAnimation;

      Screen* s = Screen::getInstance();
      s->updateRect(r);
   }
}

void Drawable::doAnim()
{
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

SDL_Rect Drawable::getRect()
{
   Animation* ca = this->animation[this->currentAnimation];
   SDL_Rect r;
   r.x = this->x;
   r.y = this->y;
   r.w = ca->getWidth();
   r.h = ca->getHeight();
   return r;
}