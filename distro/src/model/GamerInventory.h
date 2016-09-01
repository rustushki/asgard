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

#ifndef GAMER_INVENTORY_H
#define GAMER_INVENTORY_H

#include "ISaveable.h"
#include "Inventory.h"

class GamerInventory : public ISaveable, public Inventory {

public:
	~GamerInventory();
	static GamerInventory* getInstance();
   void save();

private:
	GamerInventory();

	static GamerInventory* instance;

};

#endif//GAMER_INVENTORY_H
