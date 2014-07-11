#ifndef _SYSTS_H_
#define _SYSTS_H_

#include "SDL/SDL.h"
#include "util.h"
#include "map.h"
#include "event.h"

#include <vector>


#define MAP_POSX 260
#define MAP_POSY 80
#define MENU_POSX 20
#define MENU_POSY 60
#define MENU_SIZEX 7
#define TILESET_SIZEY 20
#define TILESET_SIZEX 7

class Engine : public EventHolder {
    private:

        static Engine *instance;

    public:

        static Engine& getInstance();


        int MAP_SIZEX;
        int MAP_SIZEY;

        /// Render
        void RenderBorder(short desX, short desY, short desW, short desH, short space = 0, int bgColor = 5921370 ); // Default grey
        void RenderMenu();
        void RenderEdit();
        void RenderMap();


         /// Virtual from EventHandler
            void Render();
            void handleMouse();
            void handleKeyboard();


        Engine();
        virtual ~Engine();




        /// Atributes and properties
        //Gets the upper left point of the Tile
        int getTileX(int x, int startX);
        int getTileY(int y, int startY);
        //Sets map position
        void setMapXY(int x, int y){ mapX = x; mapY = y; return;}
        //Sets menu position
        void setMenuXY(int x, int y){ menuX = x; menuY = y; return;}
        //Sets map size in tiles
        void setMapSizeXY(int x, int y, int maxX, int maxY);
        //Seta mapa para carregar
        void setMapLoad(char* filename, int x, int y);



        /*
        void setSizeX(int sX) { sizeX = sX; }
        void setSizeY(int sY) { sizeY = sY; }
        void setStartX(int sX){ startX = sX;}
        void setStartY(int sY){ startY = sY;}

        int getSizeX()      {return sizeX;}
        int getSizeY()      {return sizeY;}
        int getStartX()     {return startX;}
        int getStartY()     {return startY;}
        int getSizeXTotal() {return sizeXTotal;}
        int getSizeYTotal() {return sizeYTotal;}
        */

        void addMapCamera(int x){
            if (startX+x+sizeX > sizeXTotal) // if outside screen
                return;
            if (startX+x+sizeX < sizeX)
                return;
            startX += x;
        }

        void addMapCameraY(int y){
            if (startY+y+sizeY > sizeYTotal) // if outside screen
                return;
            if (startY+y+sizeY < sizeY)
                return;
            startY += y;
        }

        void addTilesetCameraY(int y){
            if (tilesetStartY+y > ( (surf_map->h/TILE_SIZE) - TILESET_SIZEY) ) // if outside screen
                return;
            if (tilesetStartY+y < 0)
                return;

            tilesetStartY += y;
        }

        /// Others
        //Saves the map to file
        void saveMap();
        //Loads the tileset
        bool load_tileset(char* filename);
        bool ConvertXY(int x, int y);

        void Cleanup();

        // the MAP
        Map mapHolder;

    private:


        // tileset surface
        SDL_Surface* surf_map;


        // The map to render
        int startX;
        int startY;
        int sizeX;
        int sizeY;

        //Tileset to render
        int tilesetStartY;


        // how many tiles the whole map
        int sizeXTotal;
        int sizeYTotal;

        // the position of the map on the screen
        int mapX;
        int mapY;

        // the position of the menu on the screen
        int menuX;
        int menuY;

        // selection
        int selectionX;
        int selectionY;

        // ID
        int selectedID;
        int selectedIDend;

        // if the edit typeID is active
        bool edit;

        // Selected clip
        SDL_Rect clip;

        SDL_Rect tileClip;

        //tileset width, number of tiles in one row
        short tilesetWidth;

        std::vector<int> Types;

        //Camera on Map is startX and Y
        int cameraMenuX;
        int cameraMenuY;



};

#endif
