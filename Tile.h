#ifndef _TILE_H
#define _TILE_H

enum TileType {TILE_TYPE_WATER,TILE_TYPE_DESERT,TILE_TYPE_GRASS,TILE_TYPE_COUNT};

class Tile
{
   private:
      TileType tileType;
   public:
      virtual bool isWalkable() const = 0;
};

#endif
