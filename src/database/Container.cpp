/*****************************************************************************
 * Copyright (c) 2006 Russ Adams, Sean Eubanks, Asgard Contributors
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
#include "Container.h"

/* Constructor */
Container::Container(std::string drawableName) : StaticMapObject(drawableName)
{
   items.reserve(MAX_ITEMS);
   
   vector<Item*>::iterator currentItem;
   for(currentItem = items.begin(); currentItem != items.end(); currentItem++)
   {
      *currentItem = NULL;
   }
   
}

Container::~Container()
{
}

/* Returns number of Items in Container */
int Container::getItemCount()
{
   int validItemCount;
   vector<Item*>::iterator currentItem;
   for(currentItem = items.begin(); currentItem != items.end(); currentItem++)
   {
      if(*currentItem != NULL) validItemCount++;
   }
   return validItemCount;
}

/* Retrieve Item */
Item* Container::getItem(int index)
{
   Item* itemToReturn = NULL;
   
   if(!items.empty() && index < MAX_ITEMS)
   {
      itemToReturn = items[index];
      items[index] = NULL;
   }
   
   return itemToReturn;
}

/* Insert Item in Container */
bool Container::putItem(Item* item)
{
   bool itemAdded = false;
   
   assert(item);
   
   vector<Item*>::iterator currentItem;
   for(currentItem = items.begin(); currentItem != items.end() && !itemAdded; currentItem++)
   {
      if(*currentItem != NULL)
      {
         *currentItem = item;
         itemAdded = true;
      }
   }
   
   return itemAdded;
}

/* Can Container be opened? */
bool Container::isOpenable()
{
   return true;
}

/* What Item is cursor pointing at? */
string Container::peek(int index)
{
   assert(index < MAX_ITEMS);
   
   return items[index]->getName();
}
