//==============================================================================
#pragma once


#include "tile.h"
#include "defines.h"
#include <SDL/SDL.h>

//==============================================================================

enum
{
    TILE_TIPO_NENHUM = 0,
    TILE_TIPO_BLOCO = 1,
    TILE_TIPO_FANTASMA = 2, //Pode passar sobre
    TILE_TIPO_PLATAFORMA = 3, //Para somente na descida
    TILE_TIPO_SLOPE = 4,      //Rampas, usa Offsets
    TILE_TIPO_SPIKE = -1,
    TILE_TIPO_AGUA_FUNDO = -2,
    TILE_TIPO_AGUA_DANO = -3

};

//==============================================================================

class Tile
{
    public:
        int id;
        int tipo;

        int leftOffset;
        int rightOffset;

        void setOffset(int ixl, int ixr);

    public:

        Tile();
        ~Tile();

};






//==============================================================================



