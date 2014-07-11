#include "util.h"
#include "map.h"
#include "engine.h"
#include "button.h"

#define BTN_NUM 7
#define LAYER_NUM 5
//==============================================================================
//          GLOBAL VARIABLES
//==============================================================================
SysFont sys = SysFont::getInstance();
bool run = true;
Engine& en = Engine::getInstance();
Button btn[BTN_NUM]; // Save + 4*2 Movements
Button layers[LAYER_NUM];

//==============================================================================

void change_resolution(short w, short h)
{
    screen = SDL_SetVideoMode( w , h , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);
}
//==============================================================================

void Init()
{
    atexit(SDL_Quit);

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) exit(1);

    SDL_WM_SetCaption("SDL Window", NULL);

    screen = SDL_SetVideoMode( 1340 , 768 , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

    sys.Init_Font((char*)"arial.ttf");
}
//==============================================================================
void Cleanup()
{
    en.Cleanup();
    sys.Close_Font();
    SDL_Quit();
}
//==============================================================================
void ClearScreen()
{
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 150, 150, 150) );
}
//==============================================================================
//              EVENTS
//==============================================================================
void Events()
{

        en.handleMouse();
        en.handleKeyboard();
        for(int i = 0; i < BTN_NUM; i++)
        {
            btn[i].handleEvents();
        }
        for(int i = 0; i < LAYER_NUM; i++){
            layers[i].handleEvents();
        }


        /// Internal events
        if (event.type == SDL_QUIT)
        {
            run = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT: sys.apply_text(event.button.x, event.button.y, 12, 100,100,0, (char*)"Here!"); break;
                case SDL_BUTTON_RIGHT: break;
                case SDL_BUTTON_MIDDLE: break;
                default: ;
            }
        }

}


//==============================================================================
//              BUTTON EVENTS
//==============================================================================
void SaveMap()
{
    //SysFont::apply_text(140, 20, 12, 0,0,0 ,(char*)"EVENT!!!");
    en.saveMap();
}
void AddMapX()
{
    en.addMapCamera(1);
}
void RemoveMapX()
{
    en.addMapCamera(-1);
}
void AddMapY()
{
    en.addMapCameraY(1);
}
void RemoveMapY()
{
    en.addMapCameraY(-1);
}
void AddMenuX()
{
    en.addMapCamera(1);
}
void RemoveMenuX()
{
    en.addMapCamera(-2);
}
void AddMenuY()
{
    en.addMapCamera(-2);
}
void RemoveMenuY()
{
    en.addMapCamera(-2);
}

void TilesetAddY()
{
    en.addTilesetCameraY(1);
}

void TilesetRemoveY()
{
    en.addTilesetCameraY(-1);
}


void Layer0()
{
    en.mapHolder.activeLayer = 0;
}
void Layer1()
{
    en.mapHolder.activeLayer = 1;
}
void Layer2()
{
    en.mapHolder.activeLayer = 2;
}
void Layer3()
{
    en.mapHolder.activeLayer = 3;
}
void LayerAll()
{
    en.mapHolder.activeLayer = -1;
}
//==============================================================================
//              RENDERS
//==============================================================================
void Render()
{

    ClearScreen();

    en.Render();

    for(int i = 0; i < BTN_NUM; i++)
    {
        btn[i].Render();
    }
    for(int i = 0; i < LAYER_NUM; i++){
        layers[i].Render();
    }

    SDL_Flip(screen);
}

//==============================================================================
//              LOOPS
//==============================================================================
void Loop()
{

}
int mapSizeTotalX = 20;
int mapSizeTotalY = 15;
void ReadSize()
{
    FILE* file = fopen((char*)"size.txt", "r");
    fscanf(file, "%d-%d", &mapSizeTotalX, &mapSizeTotalY);
    if(fscanf(file, "%d:%d", &en.mapHolder.defaultID, &en.mapHolder.defaultType) ){}
    fclose(file);

    //Se carregando, tamanho = mapa
    if(mapSizeTotalX < 0) return;

    if (mapSizeTotalX < en.MAP_SIZEX) en.MAP_SIZEX = mapSizeTotalX;
    if (mapSizeTotalY < en.MAP_SIZEY) en.MAP_SIZEY = mapSizeTotalY;

    if(en.MAP_SIZEX < 20 ) en.MAP_SIZEX = 20;
    if(en.MAP_SIZEY < 15 ) en.MAP_SIZEY = 15;
}
void ObjectsInit()
{
    ReadSize();

    en.load_tileset((char*)"data/tileset/basic_tileset_32.png");
    if(mapSizeTotalX < 0 )
        en.setMapLoad((char*)"data/maps/output_map.map", en.MAP_SIZEX, en.MAP_SIZEY);
    else
        en.setMapSizeXY(en.MAP_SIZEX, en.MAP_SIZEY, mapSizeTotalX,mapSizeTotalY); /// num of display e max map xy

    en.setMenuXY(MENU_POSX, MENU_POSY);    // Position on screen
    en.setMapXY(MAP_POSX, MAP_POSY);   // Position on screen

    layers[0].Load((char*)"data/btn/layer_0.png", 2);
    layers[0].ClickAction = Layer0;
    layers[0].setXY(300, 10);

    layers[1].Load((char*)"data/btn/layer_1.png", 2);
    layers[1].ClickAction = Layer1;
    layers[1].setXY(332, 10);

    layers[2].Load((char*)"data/btn/layer_2.png", 2);
    layers[2].ClickAction = Layer2;
    layers[2].setXY(364, 10);

    layers[3].Load((char*)"data/btn/layer_3.png", 2);
    layers[3].ClickAction = Layer3;
    layers[3].setXY(396, 10);

    layers[4].Load((char*)"data/btn/layer_all.png", 2);
    layers[4].ClickAction = LayerAll;
    layers[4].setXY(428, 10);

    btn[0].Load((char*)"data/btn/btn_test.png", 3);
    btn[0].ClickAction = SaveMap;
    btn[0].setXY(60, 20);


    btn[1].Load((char*)"data/btn/btn_right.png", 2);
    btn[1].ClickAction = AddMapX;
    btn[1].setXY(MAP_POSX + en.MAP_SIZEX*TILE_SIZE + 5,
                  MAP_POSY + (int)(en.MAP_SIZEY/2)*TILE_SIZE - TILE_SIZE);

    btn[2].Load((char*)"data/btn/btn_left.png", 2);
    btn[2].ClickAction = RemoveMapX;
    btn[2].setXY(MAP_POSX - TILE_SIZE - 5,
                  MAP_POSY + (int)(en.MAP_SIZEY/2)*TILE_SIZE - TILE_SIZE );

    btn[3].Load((char*)"data/btn/btn_up.png", 2);
    btn[3].ClickAction = RemoveMapY;
    btn[3].setXY(MAP_POSX + en.MAP_SIZEX*TILE_SIZE/2 - TILE_SIZE/2,
                  MAP_POSY - TILE_SIZE - 5);

    btn[4].Load((char*)"data/btn/btn_down.png", 2);
    btn[4].ClickAction = AddMapY;
    btn[4].setXY(MAP_POSX + en.MAP_SIZEX*TILE_SIZE/2 - TILE_SIZE/2,
                  MENU_POSY + en.MAP_SIZEY*TILE_SIZE + TILE_SIZE );

    btn[5].Load((char*)"data/btn/btn_up.png", 2);
    btn[5].ClickAction = TilesetRemoveY;
    btn[5].setXY(MENU_POSX + (MENU_SIZEX/2)*TILE_SIZE + 16,
                  MENU_POSY-40);

    btn[6].Load((char*)"data/btn/btn_down.png", 2);
    btn[6].ClickAction = TilesetAddY;
    btn[6].setXY(MENU_POSX + (MENU_SIZEX/2)*TILE_SIZE + 16,
                  MENU_POSY+5+20*TILE_SIZE);


}
//==============================================================================
//               MAIN
//==============================================================================
int main(int argc, char* args[])
{
    Init();
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 150, 150, 150) );


    ObjectsInit();


    while(run)
    {
        while( SDL_PollEvent( &event ) )
        {
            Events();
        }

        //Loop();

        Render();
     }


    Cleanup();

    return 0;
}
