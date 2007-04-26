#ifndef WATER_TILE_H
#define WATER_TILE_H

#include "Tile.h"

class WaterTile : public Tile
{
   public:
      bool isWalkable() const;
};

#endif // WATER_TILE_H
