#include "timer.h"

Timer::Timer()
{
    ticks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}
void Timer::start()
{
    started = true;
    paused = false;
    ticks = SDL_GetTicks();
}
void Timer::stop()
{
    started = false;
    paused = false;
}
void Timer::pause()
{
    if (paused)
        return;

    paused = true;
    //Armazena quantos segundos foram passados em pauseTicks
    pausedTicks = SDL_GetTicks() - ticks;
}
void Timer::unpause()
{
    if(!paused)
        return;

    paused = false;
    //Armazena segundos em ticks novamente
    ticks = SDL_GetTicks() - pausedTicks;
}
unsigned int Timer::getTime()
{
    if (started == false)
        return 0;

    if (paused)
        return pausedTicks;
    else
        return (SDL_GetTicks() - ticks);
}
bool Timer::is_started()
{
    return started;
}
bool Timer::is_paused()
{
    return paused;
}

