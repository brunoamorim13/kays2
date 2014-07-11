#pragma once

#include "animation.h"
#include "timer.h"
#include "interfaces.h"
#include "vetor.h"
#include "entidade.h"
class Entidade;
class TextSplash : public Drawable , public Loopable {
    private:
        unsigned int delay;
        unsigned int tempo;
        Timer tmDelay;
        Timer tmTempo;
        float velocidade;
        Vetor pos;
        Sprite* img;
        bool estatico;
        std::string str;
    public:
        TextSplash(float x, float y, short r, short g, short b, const char*pStr, ... );
        virtual ~TextSplash();
        void setDelay(unsigned int uiDelay);
        void setTempo(unsigned int uiTempo);
        void setEstatico(bool est);
        void setVelocidade(float vel);
        void addLists();
        void removeLists();

        void render();
        void update(unsigned int dt);
};

class AnimationSplash : public Drawable, public Loopable, public Entidade {
    private:
        int n_loops;
        int n_atual;
    public:
        AnimationSplash(Animation anim, float x, float y, int loop = 1);

        void addLists();
        void removeLists();
        void setSpeeds(Vetor velocidade=Vetor(), Vetor maxVelocidade=Vetor(), Vetor aceleracao=Vetor(), Rect colision=Rect());
        void setFlags(int flag);
        void render();
        void update(unsigned int dt);
};

//---- Mostra uma barra de vida, deve ser usado normalmente por uma classe. (não ser ponteiro)
class LifeBarSplash : public Drawable, public Loopable {
    private:
        unsigned int    delay;
        Timer           timerDt;
        int*             hp;
        int*             hpMax;
        int             sizeW;
        int             sizeH;
        float           alpha;
        float           speedAlpha;
        Vetor*           pos;
        Vetor           posOffset;
        SpriteLayer     img;

    public:
        LifeBarSplash();
        virtual ~LifeBarSplash();

        void setHP(int* HP, int* HPMax);
        void setPos(Vetor* posicao);
        void setPosOffset(Vetor off);
        void setSize(int w, int h);
        void setAlphaSpeed(float speed);
        void setDelay(unsigned int msDelay);
        void update(unsigned int dt);

        void render();
        void addLists();
        void removeLists();
};

