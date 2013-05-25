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
#include "Drawable.h"
#include "Layer.h"
#include "Screen.h"

Screen* Screen::instance = NULL;

Screen::Screen() {
   this->status = SCREENSTATE_INITTING;
   this->nextFrame = SDL_GetVideoSurface();
   this->status = SCREENSTATE_IDLE;
   this->init();
}

Screen::~Screen() {
   this->status = SCREENSTATE_DESTROYING;
   SDL_FreeSurface(this->nextFrame);
   SDL_Quit();
}

Screen* Screen::getInstance() {
   if (Screen::instance == NULL)
      Screen::instance = new Screen();

   return Screen::instance;
}

void Screen::init() {
   // Setup Screen Layers


   // Gui Layer
   std::string lsName = "gui";
   this->pushLayer(new Layer(lsName));

   // Map Layer
   lsName = "map";
   this->pushLayer(new Layer(lsName));

   // TODO: Another process should initialize the background layer.
   // Special Background Layer, Drawable and Animation. Needed so that there's
   // something to out-blit transparent pixels with.

   // Create Background
   std::string abName = "backgroundAnimation";
   Animation* ab = new Animation("background.png", 800, 600, 1, 1, 1);
   std::string dbName = "testBackground";
   Drawable* db = new Drawable(dbName);
   db->addAnimation(ab, abName);
   db->play();
   lsName = "background";
   Layer* bgLayer = new Layer(lsName);
   bgLayer->insertDrawableTop(db);
   this->pushLayer(bgLayer);
}

void Screen::flip() {
   this->status = SCREENSTATE_FLIPPING;


   int l1, r1, t1, b1;
   int l2, r2, t2, b2;

   std::vector<SDL_Rect>::iterator itr;
   for (itr = this->rectsToUpdate.begin(); itr != this->rectsToUpdate.end(); itr++) {
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
      if (!(l1 > r2 || r1 < l2 || t1 > b2 || b1 < t2)) {
         SDL_Rect update;
         update.w = std::abs(std::min(r1,r2) - std::max(l1,l2));
         update.h = std::abs(std::min(b1,b2) - std::max(t1,t2));
         update.x = std::max(l1,l2);
         update.y = std::max(t1,t2);

         SDL_UpdateRect(this->nextFrame, update.x, update.y, update.w, update.h);
      }
   }

   this->rectsToUpdate.clear();
   this->status = SCREENSTATE_IDLE;
}

void Screen::prepare() {
   this->status = SCREENSTATE_PREPARING;
   std::vector<Layer*>::iterator itr;
   for (itr = this->layer.begin(); itr != this->layer.end(); itr++)
      (*itr)->update();
   this->status = SCREENSTATE_IDLE;
}

ScreenState Screen::getStatus() const {
   return this->status;
}

void Screen::insertLayer(Layer* newLayer, unsigned int position) {
   //TODO: Error handling...
   //  should throw duplicate name exception.
   //  should throw invalid position exception.
   if (position <= this->layer.size()) {
      this->layer.insert(this->layer.begin()+position, newLayer);
   }
}

void Screen::removeLayer(std::string name) {
   std::vector<Layer*>::iterator itr;
   for (itr = this->layer.begin(); itr < this->layer.end(); itr++) {
      if ((*itr)->getName() == name) {
         this->layer.erase(itr);
         break;
      }
   }
}

void Screen::appendLayer(Layer* newLayer) {
   //TODO: Error handling...
   //  should throw duplicate name exception.
   this->layer.push_back(newLayer);
}

void Screen::pushLayer(Layer* newLayer) {
   //TODO: Error handling...
   //  should throw duplicate name exception.
   std::vector<Layer*>::iterator itr = this->layer.begin();
   this->layer.insert(itr, newLayer);
}

Layer* Screen::getLayer(std::string name) const {
   std::vector<Layer*>::const_iterator itr;
   for (itr = this->layer.begin(); itr < this->layer.end(); itr++)
      if ((*itr)->getName() == name)
         return (*itr);

   return NULL;
}

void Screen::updateRect(SDL_Rect r) {
   this->rectsToUpdate.push_back(r);
   std::vector<Layer*>::const_iterator itr;
   for (itr = layer.begin(); itr < layer.end(); itr++) {
      (*itr)->updateRect(r);
   }
}

Layer* Screen::getLayerOfDrawable(Drawable* drawable) {
   std::vector<Layer*>::iterator itr;
   for (itr = layer.begin(); itr < layer.end(); itr++) {
      if ((*itr)->isDrawablePresent(drawable)) {
         return *itr;
      }
   }

   return NULL;
}
