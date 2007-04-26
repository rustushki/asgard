#ifndef GRASS_TILE_H
#define GRASS_TILE_H

#include "Tile.h"

class GrassTile : public Tile
{
   public:
      bool isWalkable() const;
};

#endif // GRASS_TILE_H
