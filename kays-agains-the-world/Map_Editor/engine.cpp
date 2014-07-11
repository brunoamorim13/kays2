#include "engine.h"

//para includes
#include "defines.h"

Engine* Engine::instance;

Engine& Engine::getInstance()
{
    if (!instance)
    {
        instance = new Engine();
    }

    return *instance;
}

Engine::Engine()
{
    surf_map = NULL;

    startX = 0;
    startY = 0;
    sizeX = 0;
    sizeY = 0;
    selectionX = 0;
    selectionY = 0;
    clip.x = 0;
    clip.y = 0;
    clip.w = TILE_SIZE;
    clip.h = TILE_SIZE;

    tileClip.x = 0;
    tileClip.y = 0;
    tileClip.w = TILESET_SIZEX*TILE_SIZE;
    tileClip.h = TILESET_SIZEY*TILE_SIZE;

    selectedID = 0;
    edit = false;


    cameraMenuX = 0;
    cameraMenuY = 0;

    selectedIDend = -1;
    tilesetStartY = 0;
    MAP_SIZEX = 30;
    MAP_SIZEY = 20;
}

Engine::~Engine()
{
    if(surf_map != NULL)
        SDL_FreeSurface(surf_map);

    if(instance)
        delete instance;
}


//==============================================================================
//             RENDERS
//==============================================================================

// Use bgColor -1 for no BG
void Engine::RenderBorder(short desX, short desY, short desW, short desH, short space, int bgColor)
{
    SDL_Rect menuBorder[5];

    /// CREATES A BORDER
    menuBorder[0].x = desX + 0;                     // Upper left -> down
    menuBorder[1].x = desX + 0;                     // Bottom left -> left
    menuBorder[2].x = desX + desW + space;          // Upper right -> down
    menuBorder[3].x = desX + 0;                     // Upper left -> left

    menuBorder[0].y = desY + 0;
    menuBorder[1].y = desY + desH + space;
    menuBorder[2].y = desY + 0;
    menuBorder[3].y = desY + 0;

    menuBorder[0].w = 1;
    menuBorder[1].w = desW + space;
    menuBorder[2].w = 1;
    menuBorder[3].w = desW + space;

    menuBorder[0].h = desH + space;
    menuBorder[1].h = 1;
    menuBorder[2].h = desH + space;
    menuBorder[3].h = 1;

    /// Background Color

    menuBorder[4].x = desX + 1;
    menuBorder[4].y = desY + 1;
    menuBorder[4].w = desW + space - 2;
    menuBorder[4].h = desH + space - 2;

    for (short i = 0; i<4; i++)
        SDL_FillRect(screen, &menuBorder[i], SDL_MapRGB(screen->format, 255,255,255));

    if (bgColor == -1)
        return;

    SDL_FillRect(screen, &menuBorder[4], bgColor);

}

void Engine::Render()
{
    RenderMap();

    RenderMenu();

    SysFont::apply_text(100, 80 + 20*TILE_SIZE + TILE_SIZE, 10, 0,0,0, (char*)"[%d,%d]", startX+(selectionX-MAP_POSX)/TILE_SIZE, startY+(selectionY-80)/TILE_SIZE  );
    SysFont::apply_text(100, 70 + 20*TILE_SIZE + TILE_SIZE, 10, 0,0,0, (char*)"[%d,%d]", (startX+(selectionX-MAP_POSX)/TILE_SIZE)*TILE_SIZE, (startY+(selectionY-80)/TILE_SIZE)*TILE_SIZE  );
}
void Engine::RenderMenu()
{
    /// TileSet Area
    tileClip.y = tilesetStartY*TILE_SIZE;
    RenderBorder(menuX-2, menuY-1,
                 (surf_map->w > TILESET_SIZEX*TILE_SIZE) ? TILESET_SIZEX*TILE_SIZE : surf_map->w,
                 (surf_map->h > TILESET_SIZEY*TILE_SIZE) ? TILESET_SIZEY*TILE_SIZE : surf_map->h, 2);

    Util::apply_surface(menuX,menuY,surf_map, screen, &tileClip);

    RenderEdit();

    /// Selection Area above tileset
    SysFont::apply_text(menuX-3, menuY-TILE_SIZE-25, 10, 0,0,0, (char*)"Selected Tile" );
    RenderBorder(menuX-3, menuY-TILE_SIZE-10, TILE_SIZE, TILE_SIZE, 1); // the 10 is just to give some space, 5 pixels



    clip.x = (selectedID % tilesetWidth) * TILE_SIZE;
    clip.y = (selectedID / tilesetWidth) * TILE_SIZE;
    clip.y -= tilesetStartY*TILE_SIZE;
    Util::apply_surface(menuX-2, menuY-TILE_SIZE-9, surf_map, screen, &clip); // The selected tile image

    ///Tileset Selection
    if(selectedID != -1){
        int multi_selectX = 0, multi_selectY = 0;
        int deslocX = 0, deslocY = 0;
        if( (selectedIDend != -1) && (selectedIDend != selectedID)) { // Quantos TILES pro Lado e Baixo
            multi_selectX = TILE_SIZE*( (selectedIDend%mapHolder.tilesetWidth)  - (selectedID%mapHolder.tilesetWidth)   );
            multi_selectY = TILE_SIZE*( (selectedIDend/mapHolder.tilesetWidth)  -  (selectedID/mapHolder.tilesetWidth)  );

            if(multi_selectX < 0) {
                deslocX = multi_selectX;
                multi_selectX = -(multi_selectX);
            }
            if(multi_selectY < 0) {
                deslocY = multi_selectY;
                multi_selectY = -(multi_selectY);
            }
        }
        SDL_Rect posSel;
        posSel.x = menuX +clip.x-1+deslocX;
        posSel.y = menuY+clip.y-1+deslocY;
        posSel.w = TILE_SIZE+multi_selectX;
        posSel.h = TILE_SIZE+multi_selectY;
        //Garante que a seleção não ultrapasse a área do tileset
        if( posSel.y < menuY ) {  //Se mais acima
                posSel.h = posSel.h - (menuY - posSel.y );
                posSel.y = menuY;
                if(posSel.h > 1000)
                    posSel.h = 0;
            }
        if( (posSel.y + posSel.h) > TILESET_SIZEY*TILE_SIZE+TILE_SIZE*2) { // Se mais abaixo
                posSel.h += TILESET_SIZEY*TILE_SIZE+TILE_SIZE*2 - (posSel.y + posSel.h);
                //Se está completamente acima da area
                if(posSel.y > TILESET_SIZEY*TILE_SIZE+TILE_SIZE)
                    posSel.h = 0;
            }
        if(posSel.h > 0)
            RenderBorder(posSel.x,posSel.y ,posSel.w, posSel.h,0,-1);



    }

    SysFont::apply_text(
                            330,
                            45,
                            10,
                            255,255,255,
                            "Layer ativo: %d",
                            mapHolder.activeLayer
                            );
}

void Engine::RenderMap()
{
    RenderBorder(mapX-1, mapY-1, sizeX*TILE_SIZE, sizeY*TILE_SIZE, 1);

    mapHolder.Render(mapX, mapY,startX, startY, sizeX, sizeY);

    //Selection
    if (selectionX && selectionY)
    {
        int multi_X = 0;
        int multi_Y = 0;
        if(selectedIDend != -1) {   //ajusta tamanho da seleção de pintar
            multi_X =  ( (selectedIDend%mapHolder.tilesetWidth)  - (selectedID%mapHolder.tilesetWidth)   );
            multi_Y =  ( (selectedIDend/mapHolder.tilesetWidth)  -  (selectedID/mapHolder.tilesetWidth)  );
        }
        RenderBorder(selectionX, selectionY, TILE_SIZE+multi_X*TILE_SIZE, TILE_SIZE+multi_Y*TILE_SIZE, 0, -1);
    }

}

void Engine::RenderEdit()
{
    if (!edit)
        return;

    mapHolder.RenderEdit(mapX, mapY, startX, startY, sizeX, sizeY);

    ///Print index
    const char* indice[10] =
    {
        "NONE = 0",
        "BLOCK = 1",
        "GHOST = 2",
        "PRATAFORM = 3", // Can pass through the block while jumping up
        "SLOPE_UP = 4",
        "SLOPE_DOWN = 5",
        "SLOPE_UP2_1 = 6",
        "SLOPE_UP2_2 = 7",
        "SLOPE_DOWN2_1 = 8",
        "SLOPE_DOWN2_2 = 9"
    };
    for (int i = 0; i < 10; i++)
        SysFont::apply_text(
                            screen->w - 120,
                            15+(i*12),
                            10,
                            255,255,255,
                            indice[i]
                            );

    /// Print alpha tileType above map
    int ID = 0;
    for (int posY = 0; posY < surf_map->h/TILE_SIZE; posY++)
    {
        for (int posX = 0; posX < tilesetWidth; posX++)
        {
            SysFont::apply_textAlpha(
                menuX + TILE_SIZE/2 + TILE_SIZE*posX,
                menuY + TILE_SIZE/2 + TILE_SIZE*posY,
                10,
                255,255,255,
                100,
                "%d", Types[ID]
            );
            ID++;
        }
    }



}
//==============================================================================
//              EVENT HANDLER
//==============================================================================
void Engine::handleMouse()
{
    if (event.type == SDL_MOUSEMOTION)
    {
        ///Over the Map
        if ( event.button.x > mapX && event.button.y > mapY )
        {
            if ( event.button.x < (mapX+sizeX*TILE_SIZE) && event.button.y < (mapY+sizeY*TILE_SIZE) )
            {
                selectionX = getTileX(event.button.x, mapX);
                selectionY = getTileY(event.button.y, mapY);
            }
        }

    }


    /// MOUSE STATE

    if(SDL_GetMouseState(NULL, NULL)& SDL_BUTTON( SDL_BUTTON_LEFT )) // If left button is pressed
    {
        /// Holding over the Map
        if ( event.button.x > mapX && event.button.y > mapY )
        {
            if ( event.button.x < (mapX+sizeX*TILE_SIZE) && event.button.y < (mapY+sizeY*TILE_SIZE) )
            {
                Tile* t = mapHolder.getTile(event.button.x + startX*TILE_SIZE - mapX,
                                  event.button.y + startY*TILE_SIZE - mapY);
                        if(t) {
                            t->tileId = selectedID; // Paste the selected Tile
                            if(selectedIDend != -1){
                                int deslocX  =  ( (selectedIDend%mapHolder.tilesetWidth)  - (selectedID%mapHolder.tilesetWidth)   );
                                int deslocY  =  ( (selectedIDend/mapHolder.tilesetWidth)  -  (selectedID/mapHolder.tilesetWidth)  );
                                for(int x = 0; x <= deslocX; x++){
                                    for(int y = 0; y <= deslocY;y++) {
                                        Tile* t2 = mapHolder.getTile(event.button.x + startX*TILE_SIZE - mapX +    x*TILE_SIZE,
                                                event.button.y + startY*TILE_SIZE - mapY     + y*TILE_SIZE);
                                        if(t2) t2->tileId = selectedID+x+ (y*mapHolder.tilesetWidth);
                                    }
                                }
                            } //Fim do paste se multi
                        } // Fim do paste

                //If nothing selected
                if ( selectedID < 0){
                    t = mapHolder.getTile(event.button.x + startX*TILE_SIZE - mapX,
                                      event.button.y + startY*TILE_SIZE - mapY);
                                        if(t) t->typeId = 0;
                }
                else{
                    t = mapHolder.getTile(event.button.x + startX*TILE_SIZE - mapX,
                                      event.button.y + startY*TILE_SIZE - mapY);
                                        if(t) t->typeId = Types[selectedID]; // Paste the selected Tile
                }
            }
        }
        /// Pressed HOLDING over the TileSet Area
        if ( event.button.x > menuX && event.button.y > menuY )
        {
            if ( event.button.x < (menuX+surf_map->w) && event.button.y < (menuY+surf_map->h) )
            {
                if ( ((event.button.y-menuY)/TILE_SIZE) < TILESET_SIZEY )
                {
                    selectedIDend = 0;
                    selectedIDend = (event.button.x-menuX) / TILE_SIZE;
                    selectedIDend += tilesetWidth * ( (event.button.y-menuY) / TILE_SIZE );
                    selectedIDend += tilesetWidth * tilesetStartY;
                    if(selectedIDend < selectedID ) {
                        selectedID = selectedIDend;
                    }
                }
            }
        } // Fim de dentro de tileset area
    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    /// Pressed over the TileSet Area
                    if ( event.button.x > menuX && event.button.y > menuY )
                    {
                        if ( event.button.x < (menuX+surf_map->w) && event.button.y < (menuY+surf_map->h) )
                        {
                            if ( ((event.button.y-menuY)/TILE_SIZE) < TILESET_SIZEY )
                            {   // Se dentro da área do TILESET
                                selectedID = 0;
                                selectedID = (event.button.x-menuX) / TILE_SIZE;
                                selectedID += tilesetWidth * ( (event.button.y-menuY) / TILE_SIZE );
                                selectedID += tilesetWidth * tilesetStartY;
                                selectedIDend = -1;

                            }

                        }
                    }

                break;

                case SDL_BUTTON_WHEELUP:
                    /// Pressed over the TileSet Area
                    if (edit) // and EDIT
                    {

                        Types[selectedID]++;

                    }

                break;
                case SDL_BUTTON_WHEELDOWN:
                    /// Pressed over the TileSet Area
                    if ( edit ) // and EDIT
                    {

                        Types[selectedID]--;

                    }

                break;
                case SDL_BUTTON_RIGHT:
                /// Pressed over the Map
                if ( event.button.x > mapX && event.button.y > mapY )
                {
                    if ( event.button.x < (mapX+sizeX*TILE_SIZE) && event.button.y < (mapY+sizeY*TILE_SIZE) )
                    {
                        Tile* t = mapHolder.getTile(event.button.x + startX*TILE_SIZE - mapX,
                                                       event.button.y + startY*TILE_SIZE - mapY);
                        if(t) selectedID = t->tileId;
                        else selectedID = -1;

                        selectedIDend = -1;


                    }
                }
                break;
                case SDL_BUTTON_MIDDLE: break;
                default: ;
            }
        }
}

void Engine::handleKeyboard()
{
    if ( event.type == SDL_KEYDOWN )
    {
        if (event.key.keysym.sym == SDLK_TAB)
        {
            edit = !edit;
        }
        if(event.key.keysym.sym == SDLK_BACKSPACE){
            selectedID = -1;
        }
    }
}


//==============================================================================
//              SETTERS AND ETC
//==============================================================================

void Engine::setMapSizeXY(int x, int y, int maxX, int maxY)
{
    //If not set just atribute the values
    if (!sizeX && !sizeY)
    {
        sizeXTotal = maxX;
        sizeYTotal = maxY;
        sizeX = x;
        sizeY = y;

        startY = (sizeYTotal-MAP_SIZEY);

        mapHolder.create_map(maxX,maxY);

    }
    else
    {
        //Convert the map and then set values
        ConvertXY(x,y);
    }
}
void Engine::setMapLoad(char* filename, int x, int y)
{

    mapHolder.Load(filename);
    sizeXTotal = mapHolder.MAP_WIDTH;
    sizeYTotal = mapHolder.MAP_HEIGHT;
    sizeX = x;
    sizeY = y;
    startY = (sizeYTotal-MAP_SIZEY);
}


bool Engine::ConvertXY(int x, int y){return true;}

//pendendo deletação
void Engine::Cleanup()
{

}

int Engine::getTileX(int x, int startX)
{
    int temp = (x-startX)/TILE_SIZE;
    return (temp*TILE_SIZE)+startX;
}
int Engine::getTileY(int y, int startY)
{
    int temp = (y-startY)/TILE_SIZE; // To disconsiderat the floating point
    return (temp*TILE_SIZE)+startY;
}

//Load tileset and set its width, number of tiles in one row
bool Engine::load_tileset(char* filename)
{
    surf_map = Util::load_image(filename);

    if (surf_map == NULL)
        return false;

    mapHolder.surf_tileset = surf_map;
    tilesetWidth = surf_map->w / TILE_SIZE;

    /// Sets Tile Default Types

    Types.clear();

    for ( int ID = 0; ID < tilesetWidth * (surf_map->h/TILE_SIZE) ; ID++)
    {
        Types.push_back(2);
    }

    return true;
}
//Save the map to file
void Engine::saveMap()
{
    mapHolder.saveMap();
    SysFont::apply_text(120, 20, 12, 200,200, 255, (char*) "Map Saved!");
}



