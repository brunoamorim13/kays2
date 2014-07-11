#pragma once

#include "tile.h"
#include "sprite.h"
#include "camera.h"
#include "defines.h"
#include <vector>
#include "teleporte.h"
#include "spriteManager.h"


#define MAP_MAX_LAYER 4

class SDL_Rect;

#include <fstream>
#include <iostream>
#include <sstream>
class Map {
    public:
            std::string checkpointMap;
    private:

        class Layer {
            public:
                Layer(Sprite* tileset){layerTileset = tileset;}
                std::vector<std::vector <Tile> >  TileList;
                int getSizeX(){return TileList.size(); }
                int getSizeY(){return TileList[0].size(); }

                void makeLayer();

                void render(int mapX, int mapY);
                void renderLayer(int mapX, int mapY, SDL_Rect* clip = NULL);

                SpriteLayer spLayer;
                Sprite* layerTileset;
        };

        std::vector<Layer*>  LayerList;
        Sprite* background;
        Sprite* tileset;
        bool  nextMap;

        SDL_Rect clipMap;
        bool isParalax;
        float paralax_x;
        float paralax_y;

    public:

        std::string nextMapName;
        // Retorna Tile* no (x,y)pixel da tela independente da camera.
        //Layer inicial 1
        Tile* getTileFromPos(int x, int y, int layer = 1);

        //Pega o Tile* pelo index x, y
        //Layer inicial 1
        Tile* getTileFromIndex(int x, int y, int layer = 1);

        int map_height,
            map_width;

        Map();
        ~Map();

        void render(int mapX, int mapY, bool isLayerImg = false);
        void renderLastLayer(int mapX, int mapY, bool isLayerImg = false);
        bool loadMap(std::string filename);
        bool loadSprite(Sprite* sp);
        bool loadBackground(Sprite* sp);

        void checkTeleports();

        void setMap(std::string map);
        bool isNextMap();
        void destroyMap();
        void loadNextMap();

        static Map MapControl;

};

