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
#include "externals.h"
#include "AnimationInteraction.h"
#include "Container.h"
#include "DialogInteraction.h"
#include "Inventory.h"

/* Constructor */
Container::Container(Drawable* drawable) : MapObject(drawable) {
   this->inv = Inventory();
}

Container::Container(Drawable* drawable, const Inventory& inv) : MapObject(drawable) {

   // Set the Inventory as the Provided Inventory.
   this->inv = Inventory(inv);

   // Construct the Animation and Dialog Interactions.
   Uint16 priority = 0;
   bool isHandledOnce = true;

   AnimationInteraction* ai = new AnimationInteraction(
        priority
      , isHandledOnce
      , "TreasureChestOpened"
   );

   // Add the Animation Interaciton.
   this->addInteraction((Interaction*) ai);

   std::string msg = "You got the " + inv.toString() + ".";
   DialogInteraction* di = new DialogInteraction(
        ++priority
      , isHandledOnce
      , msg
   );

   // Add the Dialog Interaciton.
   this->addInteraction((Interaction*) di);

}

Container::~Container() {
}


/* ------------------------------------------------------------------------------
 * inventory - Return a constant pointer to the inventory for this container.
 * The contents of the inventory may be changed, but the actually inventory
 * object may not be replaced with another one.
 */
Inventory& Container::inventory() {

   return inv;

}
