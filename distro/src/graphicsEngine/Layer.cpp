#include "Layer.h"
#include "Drawable.h"

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
 * stackAonB - Given two drawable names, and given that they are both present
 * on the layer, put drawable a on top of drawable b.
 */
void Layer::stackAonB(std::string aName, std::string bName) {
   GraphicsEngine::obtainLock();

   Drawable* a = this->getDrawableByName(aName);
   Drawable* b = this->getDrawableByName(bName);

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

void Layer::removeDrawable(std::string name) {
   GraphicsEngine::obtainLock();
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      if ((*itr)->getInstanceName().compare(name) == 0) {
         this->drawable.erase(itr);
         break;
      }
   }
   GraphicsEngine::releaseLock();
}

Drawable* Layer::getDrawableByName(std::string name) const {
   GraphicsEngine::obtainLock();
   std::vector<Drawable*>::const_iterator itr;
   Drawable* d = NULL;
   for (itr = drawable.begin(); itr < drawable.end(); itr++) {
      if ((*itr)->getInstanceName().compare(name) == 0) {
         d = *itr;
         break;
      }
   }

   GraphicsEngine::releaseLock();
   return d;
}

Drawable* Layer::getDrawableByCommonName(std::string name) const {
   GraphicsEngine::obtainLock();
   std::vector<Drawable*>::const_iterator itr;
   Drawable* d = NULL;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      if ((*itr)->getName().compare(name) == 0) {
         d = *itr;
         break;
      }
   }

   GraphicsEngine::releaseLock();
   return d;
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
         this->removeDrawable(d->getInstanceName());
         itr = this->drawable.begin();
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
