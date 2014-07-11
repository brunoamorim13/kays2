#pragma once
#include <SDL/SDL.h>

class Timer {
    private:
        unsigned int ticks;
        unsigned int pausedTicks;
        bool paused;
        bool started;
    public:
        void start();
        void stop();
        void pause();
        void unpause();
        unsigned int getTime();
        bool is_started();
        bool is_paused();

        Timer();
};

