#ifndef _TILE_H
#define _TILE_H

enum TileType {WATER,DESERT,GRASS};

class Tile
{
	private:
		TileType tileType;
	public:
		virtual bool isWalkable() const = 0;
};

#endif
