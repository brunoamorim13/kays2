#include "scroll_window.h"

//==============================================================================
//          CONSTRUCTOR
//==============================================================================
///
///
///  NOT USED, DIDNT WORK
///
///
///
SDLScrollWindow::SDLScrollWindow(int x, int y, int w, int h)
{
    winX = x;
    winY = y;
    winH = h;
    winW = w;

    cameraX = 0;
    cameraY = 0;


    en.setMapXY(x,y);
    en.setMenuXY(x,y);


    /// IF screen can hold more then max, set size = max
    if (en.getSizeXTotal() < w)
        en.setSizeX( en.getSizeXTotal() );
    else
        en.setSizeX (w/TILE_SIZE);

    if (en.getSizeYTotal() < h)
        en.setSizeY( en.getSizeYTotal() );
    else
        en.setSizeY (h/TILE_SIZE);
}


//==============================================================================
//          RENDERS
//==============================================================================

void SDLScrollWindow::RenderMap()
{
    Util::RenderBorder(winX+2,  winY-2, winW, winH, 4);

    // Sets the map offset
    en.setStartX( cameraX/TILE_SIZE );
    en.setStartY( cameraY/TILE_SIZE );
    en.RenderMap();

}
