#include "effects.h"

TextSplash::TextSplash(float x, float y, short r, short g, short b, const char*pStr, ... )
{
    char tempStr[128];
    va_list valist; // Info variavel
    va_start(valist, pStr); // Inicia argumentos
    vsprintf(tempStr, pStr, valist); // Printa str formatado
    va_end(valist); // Executa

    tempo = 1000;
    delay = 300;
    velocidade = 80;
    pos.x = x;
    pos.y = y;

    img = new Sprite();
    img->setSurface(SDLBase::txt.getTextureText(14,r,g,b,tempStr));
    str = tempStr;

    estatico = false;
    tmDelay.start();
    tmTempo.start();
}

void TextSplash::addLists(){
    addToDrawListAfter();
    addToLoopList();
}
void TextSplash::removeLists()
{
    removeFromDrawList();
    removeFromLoopList();
}

TextSplash::~TextSplash()
{
    delete img;
}

void TextSplash::render()
{   //Se o tempo tiver decorrido, retira das listas e se deleta
    if(tmTempo.getTime() > tempo) {
        removeFromDrawList();
        removeFromLoopList();
        delete(this); // suicide \o
        return;
    }
    int posX = pos.x;
    int posY = pos.y;
    if(estatico == false){
        posX -= Camera::CameraControl.getX();
        posY -= Camera::CameraControl.getY();
    }
    img->render(posX,posY, NULL );
}

void TextSplash::update(unsigned int dt)
{
    if (tmDelay.getTime() > delay)
        return;

    pos.y -= velocidade*dt*0.001f;
}

/// GET SETS
void TextSplash::setEstatico(bool est){
    estatico = est;
}
void TextSplash::setDelay(unsigned int uiDelay)
{
    delay = uiDelay;
}
void TextSplash::setTempo(unsigned int uiTempo)
{
    tempo = uiTempo;
}
void TextSplash::setVelocidade(float vel)
{
    velocidade = vel;
}

//===========================================================================
// AnimationSplash
//===========================================================================
AnimationSplash::AnimationSplash(Animation anim, float x, float y, int loop) : Entidade::Entidade(){
    n_loops = loop;
    n_atual = 0;
    an = anim;
    pos.x = x;
    pos.y = y;
    an.setFrames(an.getFrameX(),an.getNFrames(), an.getDelay(), true);
    flags = ENTIDADE_FLAG_MAP_ONLY;
    showCollision = false;
}
void AnimationSplash::setSpeeds(Vetor velocidade, Vetor maxVelocidade, Vetor aceleracao, Rect colision)
{
    vel = velocidade;
    maxVel = maxVelocidade;
    acel = aceleracao;
    col_offset = colision;
}
void AnimationSplash::setFlags(int flag){
    this->flags = flag;
}
void AnimationSplash::addLists(){
    addToDrawListAfter();
    addToLoopList();
}
void AnimationSplash::removeLists()
{
    removeFromDrawList();
    removeFromLoopList();
}
void AnimationSplash::render()
{
    Entidade::render();
}

void AnimationSplash::update(unsigned int dt)
{
    //Se tiver decorrido 1 loop
    if(an.isReady() == true) {
        n_atual++;
        //Se tiver rodado todos os loops, deleta.
        if(n_atual >= n_loops) {
            removeFromDrawList();
            removeFromLoopList();
            delete(this); // suicide \o
            return;
        }
        //Senão, reseta animação.
        an.setFrames(an.getFrameX(),an.getNFrames(), an.getDelay(), true);
    }
    Entidade::update(dt);
}
//===========================================================================
// LifeBarSplash
//===========================================================================
#include <iostream>
LifeBarSplash::LifeBarSplash()
{
    delay = 250;
    hp = hpMax = NULL;
    sizeW = 32;
    sizeH = 2;
    pos = NULL;
    alpha = 0;
    speedAlpha = 350;

}

LifeBarSplash::~LifeBarSplash()
{

}

void LifeBarSplash::setHP(int* HP, int* HPMax)
{
    hp = HP;
    hpMax = HPMax;
}
void LifeBarSplash::setSize(int w, int h)
{
    sizeH = h;
    sizeW = w;
}
void LifeBarSplash::setAlphaSpeed(float speed){
    speedAlpha = speed;
}
void LifeBarSplash::setDelay(unsigned int msDelay)
{
    delay = msDelay;
    alpha = 255;
    timerDt.start();
}
void LifeBarSplash::setPos(Vetor* posicao){
    pos = posicao;
}
void LifeBarSplash::setPosOffset(Vetor off){
    posOffset = off;
}
void LifeBarSplash::render()
{

    if(alpha <= 0 ) return;


    float x = pos->x + posOffset.x - Camera::CameraControl.getX();
    float y = pos->y + posOffset.y - Camera::CameraControl.getY();

    float hpPercent = ((float)(*hp)/(float)*hpMax); //A % de HP que o jogador possui
    int HP_w = (int)  (hpPercent*sizeW);

    SDLBase::gfx.renderFillRect(x-1,          y-1,
                                sizeW+2,  sizeH+2,
                                0,45,0, alpha);
    SDLBase::gfx.renderFillRect(x,y,sizeW,sizeH, 90,35,45,alpha);

    SDLBase::gfx.renderFillRect(x,y,HP_w,sizeH, 15,180,15,alpha);


}
void LifeBarSplash::update(unsigned int dt)
{
    if(timerDt.getTime() > delay) {
        alpha -= speedAlpha*dt*0.001f;
        if(alpha < 0 ) alpha = 0;
    }
}

void LifeBarSplash::addLists(){
    addToDrawListAfter();
    addToLoopList();
}
void LifeBarSplash::removeLists()
{
    removeFromDrawList();
    removeFromLoopList();
}
