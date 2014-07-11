//==============================================================================
#include "tile.h"
#include "defines.h"
//==============================================================================

Tile::Tile()
{
    tileId = 0;
    typeId = TILE_TYPE_NONE;

    collision_rect.x = 0;
    collision_rect.y = 0;
    collision_rect.w = TILE_SIZE;
    collision_rect.y = TILE_SIZE;
}

