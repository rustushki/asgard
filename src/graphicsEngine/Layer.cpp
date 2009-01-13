#include <vector>
#include <string>
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

void Layer::insertDrawable(Drawable* drawable, int zIndex)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   //  should throw invalid zIndex exception.
   if (zIndex >= 0 && zIndex <= this->drawable.size())
      this->drawable.insert(this->drawable.begin()+zIndex, drawable);
}

void Layer::insertDrawableTop(Drawable* drawable)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->drawable.push_back(drawable);
}

void Layer::insertDrawableBottom(Drawable* drawable)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   std::vector<Drawable*>::iterator itr = this->drawable.begin();
   this->drawable.insert(itr, new Drawable(name));
}

bool Layer::removeDrawable(std::string name)
{
   std::vector<Drawable*>::iterator itr;
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++)
   {
      if ((*itr)->getName() == name)
      {
         this->drawable.erase(itr);
         break;
      }
   }
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
   for (itr = this->drawable.begin(); itr < this->drawable.end(); itr++)
      (*itr)->updateRect(r);
}
