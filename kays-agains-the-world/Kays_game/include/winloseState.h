#pragma once

#include "state.h"
#include "sprite.h"
#include "button.h"

#include "sdlbase.h"
#include "inputmanager.h"
#include <string>


class WinLoseState : public State
{
    private:
        Sprite* background;
        std::string  texto;
        int r, g, b;
        int offX;
        Button* b_yes;
        Button* b_no;


    public:
        void load(int stack = 0);
        int unload();
        eStateType update(unsigned int dt);
        void render();

};
