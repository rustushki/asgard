#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile
{
   private:
      TileType tileType;
   public:
      virtual bool isWalkable() const = 0;
};

#endif //TILE_H
