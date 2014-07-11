#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "util.h"

enum STATE {
    STATE_OUTSIDE = 0,
    STATE_OVER = 1,
    STATE_PRESSED = 2
};

class Button {

    public:

        Button();
        ~Button();

        STATE state;

        //Renders based on state
        void handleEvents();

        void Render();

        //Function Pointer -> Event
        void (*ClickAction)(void);
        //(*funcao[f])(x);

        bool Load(char* filename, int frames);

        // Number of animations, 1 is static, 2 is static and pressend, 3 is static, press and over
        int frames;

        void setXY(int x, int y){ posX = x; posY = y; return; }

    private:

        int posX;
        int posY;
        SDL_Surface* surf_btn;
        SDL_Rect clip;


};



#endif
