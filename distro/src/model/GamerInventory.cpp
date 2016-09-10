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

#include "GamerInventory.h"
#include "Item.h"
#include "Asgard.h"
#include "QueryGenerator.h"

GamerInventory* GamerInventory::instance = NULL;

GamerInventory::GamerInventory() {
   // Register as saveable object
   Asgard::getInstance()->registerSaveable((std::shared_ptr<ISaveable>)this);
}

GamerInventory::~GamerInventory() {

}

GamerInventory* GamerInventory::getInstance() {
	if (GamerInventory::instance == NULL) {
		GamerInventory::instance = new GamerInventory();
	}

	return GamerInventory::instance;
}

void GamerInventory::save() {
   int numIter;
   unsigned int quantity;
   std::string name;
   std::vector<Item>::const_iterator iItr;
   std::shared_ptr<std::vector<Item>> tmpInvItems;
   Inventory tmpInv;

   // Sort out one Item per name so that only one database record per item name gets created later
   for(iItr = this->item.begin(); iItr < this->item.end(); iItr++) {
      if (tmpInv.countItemsByName((*iItr).getName()) == 0)
         tmpInv.addItem((*iItr));
   }

   // When querying db, pass numIter to make sure table gets (re)created once per save
   numIter = 0;
   tmpInvItems = tmpInv.getItems();
   for(iItr = (*tmpInvItems).begin(); iItr < (*tmpInvItems).end(); iItr++) {
      ++numIter;
      name = (*iItr).getName();
      quantity = this->countItemsByName(name);
      QueryGenerator::saveGamerInventory(name, quantity, numIter);
   }
}

void GamerInventory::load() {

}
