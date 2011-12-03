#include "GrassTile.h"

GrassTile::GrassTile(std::string drawableName) : Tile(drawableName)
{
   this->tileType = TILE_TYPE_GRASS;
}

bool GrassTile::isWalkable() const
{
   return true;
}
