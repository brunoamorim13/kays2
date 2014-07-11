#pragma once

#include "sprite.h"

class Animation
{
    private:
        unsigned int time;
        unsigned int delay;
        unsigned int initFrame;
        unsigned int n_frames;
        bool ready;
        bool pause;
        bool stopLast;
        bool decrease;

        SDL_Rect clipRect;

        Sprite* imagem;

    public:
        Animation();
        Animation(int delay, int n_spr, bool once);
        int update(unsigned int dt);
        void render(int x, int y);
        void setSprite(Sprite* imageFile, int clipW, int clipH);
        void setFrames(unsigned int clipX, unsigned int n_frame=1, unsigned int uDelay = 0, bool onlyOnce = false);
        void setClip(int x, int y, int w, int h);
        SDL_Rect getClip();
        void pauseAnimation(unsigned int frame=-1);
        void continueAnimation(unsigned int frame=-1);

        bool isReady();
        bool isLoop();
        unsigned int getDelay();
        unsigned int getNFrames();
        int getFrameX();
        int getFrameY();

};
