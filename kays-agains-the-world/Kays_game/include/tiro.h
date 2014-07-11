#pragma once

#include "personagem.h"
#include <math.h>
#include "effects.h"

typedef enum eTiroElemento
{
    TIRO_FLAG_COMUM  = 0,
    TIRO_FLAG_FOGO   = 0x00000001,
    TIRO_FLAG_AGUA   = 0x00000002,
    TIRO_FLAG_AR     = 0x00000004,
    TIRO_FLAG_TERRA  = 0x00000008,
    TIRO_FLAG_GHOST  = 0x00000010
}TiroElemento;

class Tiro : public Entidade {

    private:
        Timer tiroTimer;
        Timer damageTimer;
        int   tempo;
        unsigned int   delayDano;
        bool  piercing;
        bool first; //temp, identifica se primeira colisao

        void onNotValidPosition(bool isX);
    public:
        Tiro();
        Tiro(float graus, float velocidade,eEntFlag flagTiro = ENTIDADE_FLAG_PLAYER, eTiroElemento flagElemento = TIRO_FLAG_COMUM);
        eTiroElemento elemento;
        int damage;

        static std::vector<Tiro*> TiroList;

        void onExplode();


        void update(unsigned int dt);
        bool isColisaoEntidade(Entidade* objeto, int posX, int posY);
        virtual bool onRampHitX(int newX, int newY);
        void executaColisao();

        void addToTiroList();
        void removeFromTiroList();
        //Gets e Sets
        void setTempo(int msTempo);
        void setDamage(int dano);
        void setPiercing(int pierce);
        void setDelayDano(unsigned int delay);
        int getDamage();

};
