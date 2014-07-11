//==============================================================================
#ifndef _TILE_H_
#define _TILE_H_

#include "SDL/SDL.h"
#include "util.h"

//==============================================================================

enum
{
    TILE_TYPE_NONE = 0,
    TILE_TYPE_BLOCK = 1,
    TILE_TYPE_GHOST = 2,
    TILE_TYPE_PLATAFORM = 3, // Can pass through the block while jumping up
    TILE_TIPO_SLOPE_UP = 4,
    TILE_TIPO_SLOPE_DOWN,
    TILE_TIPO_SLOPE_UP2_1,
    TILE_TIPO_SLOPE_UP2_2,
    TILE_TIPO_SLOPE_DOWN2_1,
    TILE_TIPO_SLOPE_DOWN2_2
};

//==============================================================================

class Tile
{
    public:
        int tileId;
        int typeId;

        // The area of the collision, default is the entire tile.
        SDL_Rect collision_rect;

    public:

        Tile();

};






//==============================================================================

#endif

