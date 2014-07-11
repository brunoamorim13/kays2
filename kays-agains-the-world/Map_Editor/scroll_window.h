#ifndef _SCROLL_WINDOW_H_
#define _SCROLL_WINDOW_H_

#include "util.h"
#include "engine.h"


///
///
///  NOT USED, DIDNT WORK
///
///
///
class SDLScrollWindow
{
    public:



        SDLScrollWindow(int x, int y, int w, int h);

        // Renders, Use only one per instance of the class
        void RenderMenu();
        void RenderMap();

        Engine en;


    private:


        int cameraX;
        int cameraY;
        int winW;
        int winH;
        int winX;
        int winY;
        SDL_Rect clip;

};

#endif
