#pragma once

#include "vetor.h"
#include "timer.h"
#include "sprite.h"
#include <queue>
class MoveImage
{
    private:
        bool ready;
        Timer countdown;
        Vetor pos;
        Vetor dir;


        Sprite* image;

        //Armazena lista de ações... se time = 0 então ação é movimento.
        class FrameInfo
        {
            public:
                unsigned int time;
                Vetor posTarget;
                float speed;

                FrameInfo()
                {
                    time = 0;
                }
        };

        std::queue<FrameInfo> actionList;
    public:
        MoveImage();
        void update(unsigned int dt);
        void render();
        void setSprite(Sprite* imageFile);
        void setPos(Vetor vPos);
        void setPos(int x, int y);

        bool move(float moveX, float moveY);

        void addMoveToXY(int x, int y, float fspeed);
        void addMoveToXY(Vetor vpos, float fspeed);

        void addWaiting(unsigned int miliseconds);
        void addSoundEffect(int soundID, bool wait);

        bool isReady();
};

