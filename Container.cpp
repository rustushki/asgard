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

Container::Container(const Coordinate& leftCorner,list<int>& boundingBoxes,int h,int w,vector<Hardpoint*>& hpV)
   : StaticMapObject(leftCorner,boundingBoxes,h,w,hpV)
{
   items.reserve(MAX_ITEMS);
   cursor = items.begin();
}
   
int Container::getItemCount()
{
   return items.size();
}

Item* Container::getItem(string n)
{
   vector<Item*>::iterator i1;
   Item* itPtr = 0;
   for(i1 = items.begin(); i1 != items.end(); i1++)
   {
      if((*(*i1)).getName() == n)
      {
         itPtr = *i1;
         break;
      }
   }
   items.erase(i1);
   return itPtr;
}

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

bool Container::isOpenable()
{
   return true;
}

string Container::peekNext()
{
   cursor++;
   return (*(*cursor)).getName();
}

string Container::peekPrevious()
{
   cursor--;
   return (*(*cursor)).getName();
}
