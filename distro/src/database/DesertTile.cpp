#include "DesertTile.h"

DesertTile::DesertTile(std::string drawableName) : Tile(drawableName)
{
   this->tileType = TILE_TYPE_DESERT;
}

bool DesertTile::isWalkable() const
{
   return true;
}
