#ifndef _WATERTILE_H
#define _WATERTILE_H

#include "tile.h"

class WaterTile : public Tile
{
	public:
		bool isWalkable() const;
};

#endif
