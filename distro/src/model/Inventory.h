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

class Item;

class Inventory {

    public:
        Inventory();
        Inventory(const Inventory& inv);
        ~Inventory();

        void addItem(Item item);
        std::shared_ptr<std::vector<Item>> getItems();
        Inventory getItemsByName(std::string name);
        void transferAll(Inventory* inventory);
        bool transferItemToInventory(std::string name, Inventory* inventory);
        unsigned int transferItemToInventory(std::string name, Inventory* inventory, unsigned int count);

        unsigned int countUniqueItems() const;
        unsigned int countItems() const;
        unsigned int countItemsByName(std::string name) const;

        std::string toString() const;

    protected:
        std::vector<Item> item;

};

#endif//INVENTORY_H
