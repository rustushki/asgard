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
Container::Container(const Coordinate& leftCorner,list<int>& boundingBoxes,int h,int w,vector<Hardpoint*>& hpV)
   : StaticMapObject(leftCorner,boundingBoxes,h,w,hpV)
{
   items.reserve(MAX_ITEMS);
   cursor = items.begin();
}

/* Returns number of Items in Container */
int Container::getItemCount()
{
   return items.size();
}

/* Retrieve Item */
Item* Container::getItem()
{
   if(items.size() != 0)
   {
      items.erase(cursor);
      return *cursor;
   }
}

/* Insert Item in Container */
bool Container::putItem(Item* itPtr)
{
   if((itPtr != 0) && (items.size() < MAX_ITEMS))
   {
      items.push_back(itPtr);
      return true;
   }
   else
      return false;
}

/* Is Item in Container? */
bool Container::findItem(string n)
{
   vector<Item*>::iterator i1;
   for(i1 = items.begin(); i1 != items.end(); i1++)
   {
      if((*(*i1)).getName() == n)
      {
         cursor = i1;
         return true;
      }
   }
   return false;
}

/* Can Container be opened? */
bool Container::isOpenable()
{
   return true;
}

/* What Item is cursor pointing at? */
string Container::peek()
{
   return (*(*cursor)).getName();
}

/* Moves cursor to next Item */
bool Container::moveNext()
{
   /* Cannot move in empty vector */
   if(items.size() != 0)
   {
      if((cursor + 1) != items.end())
         cursor++;
      else
         cursor = items.begin();
      return true;
   }
   else
      return false;
}

/* Moves cursor to previous Item */
bool Container::movePrevious()
{
   /* Cannot move in empty vector */
   if(items.size() != 0)
   {
      if(cursor != items.begin())
         cursor--;
      else
         cursor = items.end() - 1;
      return true;
   }
   else
      return false;
}
