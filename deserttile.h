#ifndef _DESERTTILE_H
#define _DESERTTILE_H

#include "tile.h"

class DesertTile : public Tile
{
	public:
		bool isWalkable() const;
};

#endif
