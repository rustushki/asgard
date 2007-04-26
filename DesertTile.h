#ifndef DESERT_TILE_H
#define DESERT_TILE_H

#include "Tile.h"

class DesertTile : public Tile
{
   public:
      bool isWalkable() const;
};

#endif // DESERT_TILE_H
