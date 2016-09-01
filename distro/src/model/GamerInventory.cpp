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
#include "Asgard.h"

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

}
