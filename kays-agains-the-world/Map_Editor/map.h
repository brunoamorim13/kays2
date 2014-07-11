//==============================================================================
#ifndef _MAP_H_

#define _MAP_H_

#include "util.h"
#include "tile.h"
#include "defines.h"
#include <vector>

#define MAP_MAX_LAYER 4

//==============================================================================


class Map
{
    private:
        std::vector<std::vector<Tile> >      TileList;




    public:
        int tilesetWidth;

        //Create an empty map
        void create_map(int x, int y);
        void Render(int mapX, int mapY, int startX, int startY, int sizeX, int sizeY);
        void RenderEdit(int mapX, int mapY, int startX, int startY, int sizeX, int sizeY); // Render TileType

        //Save map to file
        void saveMap();

        /// Old, needs revision and delete

        SDL_Surface* surf_tileset;



        Tile* getTile(int x, int y);
        int getTileID(int x, int y);

        int MAP_HEIGHT;

        int MAP_WIDTH;

        int activeLayer;
        int defaultID;
        int defaultType;

        Map();


        bool Load(char* filename);

        static Map    MapControl;

};

//==============================================================================

#endif

