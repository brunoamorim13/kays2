//==============================================================================
#include "map.h"

#include <math.h>
//==============================================================================

#include "engine.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Map Map::MapControl;

Map::Map()
{
    surf_tileset = NULL;
    MAP_HEIGHT = MAP_WIDTH = 0;
    //ActiveLayer -1 será todos com opacividade, como será visto no jogo.
    activeLayer = 0;
    defaultID = -1;
    defaultType = 0;

}

//==============================================================================

bool Map::Load(char* filename)
{
    TileList.clear();

    TileList.resize(MAP_MAX_LAYER);

    std::ifstream myfile;
    myfile.open(filename);

    if(myfile.is_open() == false){
        printf("Nao foi possivel abrir o arquivo: %s.\n", filename);
        return false;
    }

    MAP_HEIGHT = MAP_WIDTH = 0;

    // Scan the file for the mapsize
    myfile >> MAP_WIDTH;
    myfile.ignore(20,'-');
    myfile >> MAP_HEIGHT;
    for (int tilemapID = 0; tilemapID < (int)TileList.size(); tilemapID ++) {

        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {   // Le Tiles e joga-os no TileList
                // Read Tiles and put them in TileList
                Tile tempTile;
                myfile >> tempTile.tileId; myfile.ignore(1,':');
                myfile >> tempTile.typeId;

                if(tempTile.typeId >= TILE_TIPO_SLOPE_UP){
                    int left,right;
                    myfile.ignore(1,'(');
                    myfile >> left;
                    myfile.ignore(1,':');
                    myfile >> right;
                    myfile.ignore(1,')');
                    if(left == 0){
                        if(right == 30)
                            tempTile.typeId = TILE_TIPO_SLOPE_DOWN;
                        else if (right == 14)
                            tempTile.typeId = TILE_TIPO_SLOPE_DOWN2_1;
                    }
                    else if( left == 30) {
                        if(right == 15)
                            tempTile.typeId = TILE_TIPO_SLOPE_UP2_1;
                        else if (right == 0)
                            tempTile.typeId = TILE_TIPO_SLOPE_UP;
                    }else
                    if(left == 14)
                        tempTile.typeId = TILE_TIPO_SLOPE_UP2_2;
                    else
                    if(left == 15)
                        tempTile.typeId = TILE_TIPO_SLOPE_DOWN2_2;

                }
                TileList[tilemapID].push_back(tempTile);
            }
        }
        myfile.ignore(20,'\n');
    }
    myfile.close();

    return true;

}

//==============================================================================

void Map::saveMap()
{
    ofstream file;
    file.open ("./data/maps/output_map.map",ios::out | ios::binary);


    file << MAP_WIDTH << "-" << MAP_HEIGHT << "\n";

    for (int tilemapID = 0; tilemapID < MAP_MAX_LAYER; tilemapID++) {
        int ID = 0;
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                /// RAMPAS pré configuradas
                if(TileList[tilemapID][ID].typeId > 4)
                    file << TileList[tilemapID][ID].tileId << ":" << TILE_TIPO_SLOPE_UP;
                else
                    file << TileList[tilemapID][ID].tileId << ":" << TileList[tilemapID][ID].typeId;

                if(TileList[tilemapID][ID].typeId == TILE_TIPO_SLOPE_UP) {
                    file << "(" << 30 << ":" << 0 << ")";
                } else
                if(TileList[tilemapID][ID].typeId == TILE_TIPO_SLOPE_DOWN) {
                    file << "(" << 0 << ":" << 30 << ")";
                } else
                if(TileList[tilemapID][ID].typeId == TILE_TIPO_SLOPE_UP2_1) {
                    file << "(" << 30 << ":" << 15 << ")";
                } else
                if(TileList[tilemapID][ID].typeId == TILE_TIPO_SLOPE_UP2_2) {
                    file << "(" << 14 << ":" << 0 << ")";
                } else
                if(TileList[tilemapID][ID].typeId == TILE_TIPO_SLOPE_DOWN2_1) {
                    file << "(" << 0 << ":" << 14 << ")";
                } else
                if(TileList[tilemapID][ID].typeId == TILE_TIPO_SLOPE_DOWN2_2) {
                    file << "(" << 15 << ":" << 30 << ")";
                }

                ID++;
                file << " ";
            }
            file << "\n";
        }
        file << "\n";
    }

    file.close();


/*
    FILE* file = fopen((char*)"./data/maps/output_map.map", "w+");

    fprintf(file, "%d-%d\n", MAP_WIDTH, MAP_HEIGHT);
    for (int tilemapID = 0; tilemapID < MAP_MAX_LAYER; tilemapID++) {
        int ID = 0;
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                fprintf(file, "%d:%d ", TileList[tilemapID][ID].tileId, TileList[tilemapID][ID].typeId);
                ID++;
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    */
}

//==============================================================================

void Map::Render(int mapX, int mapY, int startX, int startY, int sizeX, int sizeY)
{
    if ( surf_tileset == NULL )
        return;
    if (sizeX < 0 )
        return;
    if (sizeY < 0)
        return;

    // Calculates the number of tiles horizontaly
    tilesetWidth = surf_tileset->w / TILE_SIZE;

    //Gets the starting position
    int startID = getTileID(startX*TILE_SIZE, startY*TILE_SIZE);

    for(int y = 0, ID = startID; y < sizeY; y++) {
		for(int x = 0;x < sizeX; x++, ID++) {
		    for(int tilemapID = 0; tilemapID < (int)TileList.size(); tilemapID++){

		        int alpha = 255;

                //ActiveLayer -1 será todos com opacividade, como será visto no jogo.
		        if( (activeLayer != -1) &&(activeLayer != tilemapID) ) {
                    int dif = abs( activeLayer - tilemapID);
                    alpha -= dif*60;
		        }


                if ( TileList[tilemapID][ID].tileId == -1)
                {
                    continue;
                } else
                if ( TileList[tilemapID][ID].typeId == TILE_TYPE_NONE )
                {
                    continue;
                }

                // Lugar da tela aonde aplicar a imagem
                // Screen location to apply image
                int destX = mapX + (x * TILE_SIZE);
                int destY = mapY + (y * TILE_SIZE);



                SDL_Rect clip;
                // Qual tile cortar dependendo do TileID
                // Which tile to crop based on TileID
                clip.x = (TileList[tilemapID][ID].tileId % tilesetWidth) * TILE_SIZE;
                clip.y = (TileList[tilemapID][ID].tileId / tilesetWidth) * TILE_SIZE;
                // Tamanho do pedaço a cortar
                // Size of the piece to chop
                clip.h = TILE_SIZE;
                clip.w = TILE_SIZE;

                // Adicionar verificação caso esteja fora da tela ??
                // Add verification in case it's offscreen ??
                Util::apply_surface(destX, destY, surf_tileset, screen, &clip, alpha); // Render
                }
		}
		ID+= MAP_WIDTH - (sizeX); // Adds the rest
		//     0 0 0 0 0 0
		//     0 1 1 2 2 2
		//     2 1 1 1 0 0

    }
}

//==============================================================================

Tile* Map::getTile(int x, int y)
{ // Retorna Tile no (x,y) da tela
    // Return Tile at the (x,y) of the screen
    if(activeLayer == -1) return NULL;

    unsigned int ID = 0;

    ID = x / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (y / TILE_SIZE));

    if(ID < 0 || ID >= TileList[activeLayer].size()) {
    	return NULL;
    }

    return &TileList[activeLayer][ID];
}

int Map::getTileID(int x, int y)
{ // Retorna Tile no (x,y) da tela
    // Return Tile at the (x,y) of the screen
    unsigned int ID = 0;

    ID = x / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (y / TILE_SIZE));

    if(ID < 0 || ID >= TileList[0].size()) {
    	return 0;
    }

    return ID;
}

/// NEW FUNCTIONS

void Map::create_map(int x, int y)
{
    TileList.clear();

    MAP_WIDTH = x;
    MAP_HEIGHT = y;

    //Controla tamanho
    if (MAP_WIDTH < Engine::getInstance().MAP_SIZEX) Engine::getInstance().MAP_SIZEX = MAP_WIDTH;
    if (MAP_HEIGHT < Engine::getInstance().MAP_SIZEY) Engine::getInstance().MAP_SIZEY = MAP_HEIGHT;

    if(Engine::getInstance().MAP_SIZEX < 20 ) Engine::getInstance().MAP_SIZEX = 20;
    if(Engine::getInstance().MAP_SIZEY < 15 ) Engine::getInstance().MAP_SIZEY = 15;
    //Fim controle tamanho

    TileList.resize(MAP_MAX_LAYER);

    for (int cordY = 0; cordY < y; cordY++)
    {
        for (int cordX = 0; cordX < x; cordX++)
        {
            Tile tempTile;
            tempTile.tileId = defaultID;
            tempTile.typeId = defaultType;
            TileList[0].push_back(tempTile); // Fill TileList with empty Tiles (not renderable)

            Tile tempTile2;
            tempTile2.tileId = -1;
            tempTile2.typeId = defaultID;
            TileList[1].push_back(tempTile2); // Fill TileList with empty Tiles (not renderable)

            Tile tempTile3;
            tempTile3.tileId = -1;
            tempTile3.typeId = defaultID;
            TileList[2].push_back(tempTile3); // Fill TileList with empty Tiles (not renderable)

            Tile tempTile4;
            tempTile4.tileId = -1;
            tempTile4.typeId = defaultID;
            TileList[3].push_back(tempTile4); // Fill TileList with empty Tiles (not renderable)
        }
    }
}

//Renderiza os IDs do tile selecionado sobre os TILES
void Map::RenderEdit(int mapX, int mapY, int startX, int startY, int sizeX, int sizeY)
{
    if(activeLayer == -1) return;
    if (sizeX < 0 )
        return;
    if (sizeY < 0)
        return;

    /// Print alpha tileType above map
    //Gets the starting position
    int startID = getTileID(startX*TILE_SIZE, startY*TILE_SIZE);

    for(int posY = 0, ID = startID; posY < sizeY; posY++)
    {
		for(int posX = 0;posX < sizeX; posX++, ID++)
		{
            SysFont::apply_textAlpha(
                mapX + TILE_SIZE/2 + TILE_SIZE*posX,
                mapY + TILE_SIZE/2 + TILE_SIZE*posY,
                10,
                255,255,255,
                100,
                "%d", TileList[activeLayer][ID].typeId
            );
        }
        ID+= MAP_WIDTH - (sizeX); // Adds the rest
    }
}

