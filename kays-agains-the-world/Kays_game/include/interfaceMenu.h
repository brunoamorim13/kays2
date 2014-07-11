#pragma once

#include "map.h"
#include "player.h"
#include "sdlbase.h"
#include "quest.h"


class InterfaceMenu {
    public:
        static InterfaceMenu InterfaceControl;

        InterfaceMenu();
        void render();

        Sprite* spriteSheet;
        Sprite* spriteGelo;
        Sprite* spriteFogo;

    private:
        void renderBar();
        void renderEnergy();
        void renderQuest();


};
