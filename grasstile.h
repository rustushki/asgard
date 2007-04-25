#ifndef _GRASSTILE_H
#define _GRASSTILE_H

#include "tile.h"

class GrassTile : public Tile
{
	public:
		bool isWalkable() const;
};

#endif
