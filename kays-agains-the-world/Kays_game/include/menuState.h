#pragma once

#include "state.h"
#include "sprite.h"
#include "button.h"

class StateMenu : public State
{
    private:
        Sprite* background;
        std::vector<Button*> BtnList;
        Button* btn_start;
        Button* btn_load;
        Button* btn_exit;
        int stack;

    public:
        void load(int stack = 0);
        int unload();
        eStateType update(unsigned int dt);
        void render();
};

