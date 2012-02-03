/*****************************************************************************
 * Copyright (c) 2007 Russ Adams, Sean Eubanks, Asgard Contributors
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

#ifndef CONTAINER_H
#define CONTAINER_H

#include "externals.h"
#include "MapObject.h"
#include "Item.h"

class Container : public MapObject
{
   public:
      Container(std::string drawableName);
      ~Container();
      int getItemCount();
      Item* getItem(int index);
      bool putItem(Item* item);
      bool isOpenable();
      std::string peek(int index);
      
   private:
      const static int MAX_ITEMS = 15;
      std::vector<Item*> items;
};

#endif //CONTAINER_H
