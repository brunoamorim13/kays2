//==============================================================================
#include "tile.h"
//==============================================================================

Tile::Tile()
{
    id = 0;
    tipo = TILE_TIPO_NENHUM;
    leftOffset = 30;
    rightOffset = 0;

}

Tile::~Tile()
{
}

void Tile::setOffset(int ixl, int ixr)
{
    leftOffset = ixl;
    rightOffset = ixr;

}

