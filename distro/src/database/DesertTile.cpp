#include "DesertTile.h"

DesertTile::DesertTile(Drawable* drawable) : Tile(drawable)
{
   this->tileType = TILE_TYPE_DESERT;
}

bool DesertTile::isWalkable() const
{
   return true;
}
