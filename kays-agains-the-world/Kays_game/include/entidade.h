#pragma once

#include "map.h"
#include "gameObject.h"
#include "interfaces.h"
#include "animation.h"
#include "timer.h"
#include <time.h>

#include "quest.h"

class Map;

typedef enum eEntFlag
{    // Adiciona com | e testa com &
    ENTIDADE_FLAG_NENHUM = 0,
    ENTIDADE_FLAG_FISICA = 1,                   //Fisica afeta
    ENTIDADE_FLAG_PLAYER = 2,                   //É o jogador
    ENTIDADE_FLAG_TIRO_INIMIGO = 4,             //É um tiro do inimigo, afeta player
    ENTIDADE_FLAG_NPC = 8,                      //É um NPC
    ENTIDADE_FLAG_INIMIGO = 16,                 //É um inimigo
    ENTIDADE_FLAG_TIRO_PLAYER  = 32,            //É um tiro do Player, afeta inimigo
    ENTIDADE_FLAG_MAP_ONLY= 64,                 //Só colide com o mapa
    ENTIDADE_FLAG_MAP_ONLY_COLIDE = 128,        //Só colide com o mapa, porém, propaga colisões com entidades.
    ENTIDADE_FLAG_COLIDE_ONLY = 256,
    ENTIDADE_FLAG_BOSS = 512
}EntFlag;

class Entidade : public GameObject
{
    protected:
        //Animation an;

        bool canDoJump;
        Timer jumpTimer;

        std::vector<Entidade*> entidadeColidida;
        Vetor colVel; //Velocidade que estava quando colidiu
    public:
        Animation an;
        Vetor acel;
        Vetor vel;
        Vetor maxVel;
        Vetor lastMaxVel;
        Vetor extVel;
        int flags;
        bool dead;
        //Controle de movimento
        float gravity_speed;
        float walking_aceleration;
        float stop_aceleration;
    public:
        static std::vector<Entidade*> EntidadeList;
        void addToEntidadeList();
        void removeFromEntidadeList();

        Entidade();
        virtual ~Entidade();
        Entidade(float x, float y);

        virtual void update(unsigned int dt);
        virtual void render();
        virtual void executaColisao();
        void setDirecao(float graus, float velocidade);

        bool isValidTile(Tile* tile);
        bool isColisaoRetangulo(float fX, float fY, float fW, float fH);
        virtual bool isColisaoEntidade(Entidade* objeto, int posX, int posY);
        virtual bool isValidPosition(int newX, int newY, float goX, float goY);
            virtual bool onRampHitX(int newX, int newY);
            virtual bool onRampHitY(int newX, int newY);
        virtual void onNotValidPosition(bool isX);

        virtual void move(float moveX, float moveY);

    public: //Getter and Setter
        bool isFlag(int f);

        void setSprite(Sprite* sp_obj, int f_width, int f_height,int boxX=0, int boxY=0, int boxW=0, int boxH=0);
        //Muda o intervalo e quantidade de frames da animação
        void setAnimation(unsigned int delay, unsigned int n_frames);
        void setFrames(unsigned int clipX, unsigned int n_frame, unsigned int uDelay = 0, bool onlyOnce = false);
        void setColisao(Entidade* ent);

        bool isInvencible();
        void setInvencible(int delayInv);
    protected:
        bool invencible;
        Timer timerInvencible;
        unsigned int tempoInvencible;
};
