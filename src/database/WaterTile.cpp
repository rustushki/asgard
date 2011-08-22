#include "WaterTile.h"

WaterTile::WaterTile(std::string drawableName) : Tile(drawableName)
{
   this->tileType = TILE_TYPE_WATER;
}

bool WaterTile::isWalkable() const
{
   return true;
}
