#include "Layer.h"
#include "Drawable.h"

Layer::Layer(std::string name)
{
   this->name = name;
}

Layer::~Layer()
{

}

std::string Layer::getName()
{
   return this->name;
}

LayerState Layer::getStatus()
{
   return this->status;
}

void Layer::insertDrawable(Drawable* drawable, unsigned int zIndex)
{
   GraphicsEngine::obtainLock();
   //TODO: Error handling...
   //  should throw duplicate name exception.
   //  should throw invalid zIndex exception.
   if (zIndex >= 0 && zIndex <= this->drawable.size())
      this->drawable.insert(this->drawable.begin()+zIndex, drawable);
   GraphicsEngine::releaseLock();
}

void Layer::insertDrawableTop(Drawable* drawable)
{
   GraphicsEngine::obtainLock();
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->drawable.push_back(drawable);
   GraphicsEngine::releaseLock();
}

void Layer::insertDrawableBottom(Drawable* drawable)
{
   GraphicsEngine::obtainLock();
   //TODO: Error handling...
   //  should throw duplicate name exception.
   std::vector<Drawable*>::iterator itr = this->drawable.begin();
   this->drawable.insert(itr, new Drawable(name));
   GraphicsEngine::releaseLock();
}

void Layer::removeDrawable(std::string name)
{
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

Drawable* Layer::getDrawableByName(std::string name) {
   GraphicsEngine::obtainLock();
   std::vector<Drawable*>::iterator itr;
   Drawable* d = NULL;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      if ((*itr)->getInstanceName().compare(name) == 0) {
         d = *itr;
         break;
      }
   }

   GraphicsEngine::releaseLock();
   return d;
}

void Layer::update()
{
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
}

void Layer::updateRect(SDL_Rect r)
{
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++) {
      Drawable* d = (*itr);
      if (d->hasBeenHidden && d->toBeRemoved) {
         this->removeDrawable(d->getInstanceName());
         delete d;
      } else {
         d->updateRect(r);
      }
   }
}
