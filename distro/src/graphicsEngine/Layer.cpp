#include "Drawable.h"
#include "Layer.h"
#include "GraphicsEngine.h"

Layer::Layer(std::string name) {
   this->name = name;
}

Layer::~Layer() {

}

std::string Layer::getName() {
   return this->name;
}

LayerState Layer::getStatus() {
   return this->status;
}

/* ------------------------------------------------------------------------------
 * stackAonB - Given two drawables, and given that they are both present on the
 * layer, put drawable a on top of drawable b.
 */
void Layer::stackAonB(Drawable* a, Drawable* b) {
   GraphicsEngine::obtainLock();

   std::vector<Drawable*>::iterator aItr = find(drawable.begin(), drawable.end(), a);
   std::vector<Drawable*>::iterator bItr = find(drawable.begin(), drawable.end(), b);

   if (aItr > bItr) {
      return;
   } else {

      // Construct a new drawable vector.  Effectively, splice out A from it's
      // current position, and insert it just before B.
      std::vector<Drawable*> newDrawableVec;

      // All elements from beginning of drawable vec up to A.
      newDrawableVec.insert(newDrawableVec.end(), drawable.begin(), aItr);

      // All elements in drawable vec after A up to B.
      newDrawableVec.insert(newDrawableVec.end(), aItr+1, bItr);

      // Insert B.
      newDrawableVec.insert(newDrawableVec.end(), b);

      // Insert A.
      newDrawableVec.insert(newDrawableVec.end(), a);

      // All elements in drawable vec after B to the end.
      newDrawableVec.insert(newDrawableVec.end(), bItr+1, drawable.end());

      // The new Drawable Vector replaces the old one.
      this->drawable = newDrawableVec;
   }

   GraphicsEngine::releaseLock();
}

bool Layer::isDrawablePresent(Drawable* d) {
   GraphicsEngine::obtainLock();

   bool found = false;
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      if ((*itr) == d) {
         found = true;
         break;
      }
   }

   GraphicsEngine::releaseLock();
   return found;
}

void Layer::insertDrawable(Drawable* drawable, unsigned int zIndex) {
   GraphicsEngine::obtainLock();
   //TODO: Error handling...
   //  should throw duplicate name exception.
   //  should throw invalid zIndex exception.
   if (zIndex <= this->drawable.size())
      this->drawable.insert(this->drawable.begin()+zIndex, drawable);
   GraphicsEngine::releaseLock();
}

void Layer::insertDrawableTop(Drawable* drawable) {
   GraphicsEngine::obtainLock();
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->drawable.push_back(drawable);
   GraphicsEngine::releaseLock();
}

void Layer::insertDrawableBottom(Drawable* drawable) {
   GraphicsEngine::obtainLock();
   //TODO: Error handling...
   //  should throw duplicate name exception.
   std::vector<Drawable*>::iterator itr = this->drawable.begin();
   this->drawable.insert(itr, new Drawable(name));
   GraphicsEngine::releaseLock();
}

void Layer::removeDrawable(Drawable* drawable) {
   GraphicsEngine::obtainLock();
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      if ((*itr) == drawable) {
         this->drawable.erase(itr);
         break;
      }
   }
   GraphicsEngine::releaseLock();
}

void Layer::update() {
   // Update Drawables for this Layer.

   // Order is very important here.  Move and Swap need to happen before
   // Animating.
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr != this->drawable.end(); itr++)
      (*itr)->doMove();
   for (itr = this->drawable.begin(); itr != this->drawable.end(); itr++)
      (*itr)->doSwap();
   for (itr = this->drawable.begin(); itr != this->drawable.end(); itr++)
      (*itr)->doAnim();
   for (itr = this->drawable.begin(); itr != this->drawable.end(); itr++)
      (*itr)->doHide();

   // Unload any hidden and removed Drawables.
   for (itr = this->drawable.begin(); itr != this->drawable.end(); itr++) {
      Drawable* d = (*itr);
      if (d->hasBeenHidden && d->toBeRemoved) {
         itr = this->drawable.erase(itr);
         itr--;
      }
   }
}

void Layer::updateRect(SDL_Rect r) {
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      Drawable* d = (*itr);
      if (!d->hasBeenHidden || !d->toBeRemoved) {
         d->updateRect(r);
      }
   }
}
