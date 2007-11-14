#include "DesertTile.h"

DesertTile::DesertTile() : Tile()
{
   this->tileType = TILE_TYPE_DESERT;
}

bool DesertTile::isWalkable() const
{
   return true;
}
