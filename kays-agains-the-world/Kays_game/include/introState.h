#pragma once

#include "state.h"

#include "sprite.h"
#include "timer.h"
#include "animation.h"
#include "inputmanager.h"
#include "moveimage.h"
class IntroState : public State
{
   private:
        MoveImage anim;
        Sprite* logo;
        Sprite* background;
        Sprite* story1;
        Sprite* story2;
        int sub_state;
        Timer time;
    public:
        void load(int stack = 0);
        int unload();
        StateType update(unsigned int dt);
        void render();
};
