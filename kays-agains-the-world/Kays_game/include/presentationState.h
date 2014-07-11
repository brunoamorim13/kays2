#pragma once

#include "state.h"

#include "sprite.h"
#include "timer.h"
#include "animation.h"
#include "inputmanager.h"
#include "moveimage.h"
class PresentationState : public State
{
    private:
        MoveImage anim;
        Sprite* background;
        Sprite* story1;
        Sprite* story2;
        Sprite* lvl1_1;
        Sprite* lvl1_2;
        Sprite* lvl1_3;
        Sprite* lvl1_4;
        Sprite* lvl1_5;
        Sprite* lvl1_6;
        Sprite* lvl1_7;
        Sprite* lvl1_8;
        Sprite* lvl2;
        Sprite* lvl3;
        Sprite* lvl4;

        int sub_state;
        Timer time;

        StateType animationStage1(unsigned int dt);
        StateType animationStage2(unsigned int dt);
        StateType animationStage3(unsigned int dt);
        StateType animationStage4(unsigned int dt);
        StateType animationStageBoss(unsigned int dt);
    public:
        void load(int stack = 0);
        int unload();
        StateType update(unsigned int dt);
        void render();
        int stack;
};

