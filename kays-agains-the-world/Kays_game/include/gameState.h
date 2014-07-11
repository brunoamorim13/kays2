#pragma once

#include "state.h"
#include "map.h"
#include "player.h"
#include "tiro.h"
#include "inimigo.h"
#include "itemobj.h"
#include "interfaceMenu.h"
#include "quest.h"
#include "npc.h"
#include "spriteManager.h"
#include "player.h"
#include "timer.h"
#include "save.h"
#include "presentationState.h"

class StateGame : public State
{
    private:
        Sprite* sp_player;
        Sprite* sp_bg;
        Sprite* sp_item;
        Sprite* sp_bar;

        Sprite* sp_magiaGelo;
        Sprite* sp_magiaFogo;

        NPC* npc;
        Timer timerDead;

        PresentationState cutscene;

    public:
        void load(int stack = 0);
        int unload();
        void destroyObjetos();
        eStateType update(unsigned int dt);
        void render();
        int stack;

};

