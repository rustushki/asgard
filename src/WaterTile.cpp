#include "WaterTile.h"

WaterTile::WaterTile() : Tile()
{
   this->tileType = TILE_TYPE_WATER;
}

bool WaterTile::isWalkable() const
{
   return true;
}
