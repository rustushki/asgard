/*****************************************************************************
 * Copyright (c) 2012 Russ Adams, Sean Eubanks, Asgard Contributors
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

#ifndef INVENTORY_H
#define INVENTORY_H

#include "externals.h"
#include "Item.h"

class Inventory {

    public:
        Inventory();
        ~Inventory();

        void addItem(Item item);
        Inventory getItemsByName(std::string name);
        void mergeInventory(const Inventory* inventory);
        bool transferItemToInventory(std::string name, const Inventory* inventory);

        unsigned int countUniqueItems() const;
        unsigned int countItems() const;
        unsigned int getCountOfItemByName(std::string name) const;


    private:
        std::vector<Item> item;


};

#endif//INVENTORY_H
