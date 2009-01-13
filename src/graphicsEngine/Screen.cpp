#include <iostream>
#include <algorithm>
#include "Screen.h"

Screen* Screen::instance = NULL;

Screen::Screen()
{
   this->status = SCREENSTATE_INITTING;
   SDL_Init(SDL_INIT_VIDEO);

   SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, 16, SDL_DOUBLEBUF);

   this->nextFrame = SDL_GetVideoSurface();
   this->status = SCREENSTATE_IDLE;
}

Screen::~Screen()
{
   this->status = SCREENSTATE_DESTROYING;
   SDL_FreeSurface(this->nextFrame);
}

Screen* Screen::getInstance()
{
   if (Screen::instance == NULL)
      Screen::instance = new Screen();

   return Screen::instance;
}

bool Screen::flip()
{
   this->status = SCREENSTATE_FLIPPING;


   uint l1, r1, t1, b1;
   uint l2, r2, t2, b2;

   std::vector<SDL_Rect>::iterator itr;
   for (itr = this->rectsToUpdate.begin(); itr != this->rectsToUpdate.end(); itr++)
   {
      // Compute the sides of the animation.
      l1 = 0;
      r1 = Screen::WIDTH;
      t1 = 0;
      b1 = Screen::HEIGHT;
      
      // Compute the sides of the provided rect.
      l2 = (*itr).x;
      r2 = (*itr).x+(*itr).w;
      t2 = (*itr).y;
      b2 = (*itr).y+(*itr).h;

      // Does the current animation intersect with the provided rect?  If so,
      // update the animation.
      if (!(l1 > r2 || r1 < l2 || t1 > b2 || b1 < t2))
      {
         SDL_Rect update;
         update.w = std::min(r1,r2) - std::max(l1,l2);
         update.h = std::min(b1,b2) - std::max(t1,t2);
         update.x = std::max(l1,l2);
         update.y = std::max(t1,t2);

         SDL_UpdateRect(this->nextFrame, update.x, update.y, update.w, update.h);
      }
   }

   this->rectsToUpdate.clear();
   this->status = SCREENSTATE_IDLE;
}

bool Screen::prepare()
{
   this->status = SCREENSTATE_PREPARING;
   std::vector<Layer*>::iterator itr;
   for (itr = this->layer.begin(); itr != this->layer.end(); itr++)
      (*itr)->update();
   this->status = SCREENSTATE_IDLE;
}

ScreenState Screen::getStatus() const
{
   return this->status;
}

void Screen::insertLayer(Layer* newLayer, int position)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   //  should throw invalid position exception.
   if (position >= 0 && position <= this->layer.size())
      this->layer.insert(this->layer.begin()+position, newLayer);
}

bool Screen::removeLayer(std::string name)
{
   std::vector<Layer*>::iterator itr;
   for (itr = this->layer.begin(); itr < this->layer.end(); itr++)
   {
      if ((*itr)->getName() == name)
      {
         this->layer.erase(itr);
         break;
      }
   }
}

void Screen::appendLayer(Layer* newLayer)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->layer.push_back(newLayer);
}

void Screen::pushLayer(Layer* newLayer)
{
   //TODO: Error handling...
   //  should throw duplicate name exception.
   std::vector<Layer*>::iterator itr = this->layer.begin();
   this->layer.insert(itr, newLayer);
}

Layer* Screen::getLayer(std::string name) const
{
   std::vector<Layer*>::const_iterator itr;
   for (itr = this->layer.begin(); itr < this->layer.end(); itr++)
      if ((*itr)->getName() == name)
         return (*itr);
}

void Screen::updateRect(SDL_Rect r)
{
   this->rectsToUpdate.push_back(r);
   std::vector<Layer*>::const_iterator itr;
   for (itr = this->layer.begin(); itr < this->layer.end(); itr++)
      (*itr)->updateRect(r);
}
