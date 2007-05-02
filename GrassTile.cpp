#include "GrassTile.h"

GrassTile::GrassTile() : Tile()
{
   this->tileType = TILE_TYPE_GRASS;
}

bool GrassTile::isWalkable() const
{
   return true;
}
