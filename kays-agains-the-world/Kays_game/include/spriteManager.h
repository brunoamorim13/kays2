#pragma once

#define N_SPRITES 256

enum {
    SPRITE_BOOMER = 0,
    SPRITE_SLIME_SIMPLE,
    SPRITE_ESQUELETO,
    SPRITE_PLAYER,
    SPRITE_SLIME_GOD,
    SPRITE_NPC1, // 5
    SPRITE_NPC2, // 6
    SPRITE_NPC3, // 7
    SPRITE_CYBORG_SLIME,// 8
    SPRITE_NPC4,// 9
    SPRITE_TILESET,
    SPRITE_FOGO,
    SPRITE_AR,
    SPRITE_TIRO,
    SPRITE_TERRA,
    SPRITE_BALL,
    SPRITE_GELO,
    SPRITE_MAGO_CORROMPIDO,//17
    SPRITE_NECROMANCER//18
};


#include "sprite.h"

class SpriteManager{
    public:
        static SpriteManager SpriteControl;
        SpriteManager();

        Sprite* getSprite(int index);
        void loadSprite(const char* filename, int index);
        void deleteSprite(int index);
        void deleteAllSprites();
    private:
        Sprite* vetorSprite[N_SPRITES];

};
