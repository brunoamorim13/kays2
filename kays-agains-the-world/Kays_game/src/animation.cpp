#include "animation.h"

Animation::Animation()
{
    ready = false;
    this->delay = 100;
    n_frames = 1;

    time = 0;
    ready = false;
    initFrame = 0;
    decrease = false;
    stopLast = false;
    pause = false;
    clipRect.x = clipRect.y = clipRect.w = clipRect.h = 0;
}
Animation::Animation(int delay, int n_spr, bool once)
{
    ready = false;
    this->delay = delay;
    n_frames = n_spr;

    time = 0;
    ready = false;
    initFrame = 0;
    decrease = false;
    stopLast = once;
    clipRect.x = clipRect.y = clipRect.w = clipRect.h = 0;
}
void Animation::render(int x, int y)
{
    imagem->render(x,y, &clipRect);
}
int Animation::update(unsigned int dt)
{
    if(pause) return -2;
    if(stopLast && ready) return -1;

    time += dt;

    int frameSkip = time/delay;

    if(decrease)
        clipRect.y -= clipRect.h*frameSkip;
    else
        clipRect.y += clipRect.h*frameSkip;

    int limit = clipRect.h*n_frames;

    if(decrease == false && clipRect.y >= (int)( initFrame*clipRect.h + limit ) )
    {
        if(stopLast)
            clipRect.y -= clipRect.h;
        else
            clipRect.y = initFrame;
        ready = true;
    } else
    if(decrease == true && clipRect.y <= (int)( initFrame*clipRect.h - limit ) )
    {
        if(stopLast)
            clipRect.y += clipRect.h;
        else
            clipRect.y = initFrame;
        ready = true;
    }


    //Reduz o tempo utilizado
    if(frameSkip >= 1) {
        time -= delay*frameSkip;
    }

    return frameSkip;
}

void Animation::setSprite(Sprite* imageFile, int clipW, int clipH)
{
    imagem = imageFile;
    clipRect.w = clipW;
    clipRect.h = clipH;
}
void Animation::setClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}
SDL_Rect Animation::getClip() {
    return clipRect;
}
bool Animation::isReady()
{
    if(stopLast == false) return false;
    return ready;
}
bool Animation::isLoop()
{
    return !stopLast;
}


void Animation::setFrames(unsigned int clipX, unsigned int n_frame, unsigned int uDelay, bool onlyOnce)
{
    clipRect.x = clipX*clipRect.w;
    if(uDelay) //Se for zero, permana
        delay = uDelay;
    n_frames = n_frame;
    stopLast = onlyOnce;
    ready = false;
}

unsigned int Animation::getDelay(){
    return delay;
}
unsigned int Animation::getNFrames(){
    return n_frames;
}
void Animation::pauseAnimation(unsigned int frame){
    pause = true;
    if(frame < 0) {
        return;
    }
    clipRect.y = frame*clipRect.h;
}
void Animation::continueAnimation(unsigned int frame){
    pause = false;
    time = 0;
    if(frame < 0) {
        return;
    }
    clipRect.y = frame*clipRect.h;
}
int Animation::getFrameX()
{
    return clipRect.x/clipRect.w;
}
int Animation::getFrameY()
{
    return clipRect.y/clipRect.h;
}
