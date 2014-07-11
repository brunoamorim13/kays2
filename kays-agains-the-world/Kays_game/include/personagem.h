#pragma once

#include "entidade.h"
#include "effects.h"
#include "timer.h"

enum
{
    ACT_RIGHT = 0,
    ACT_LEFT = 1,
    ACT_STAND_LEFT,
    ACT_STAND_RIGHT,
    ACT_STOPPING,
    ACT_NONE
};
enum
{
    ACT_TYPE_NONE = 0,
    ACT_TYPE_JUMP,
    ACT_TYPE_ATTACK=4
};
class Personagem : public Entidade
{
     public:
        virtual ~Personagem();
        Personagem();
        Personagem(float x, float y);
        virtual void update(unsigned int dt);
        virtual void executaColisao();
        virtual void render();
    protected:
        int  actionMovement; //parado=0, andando esq = -1, dir = 1
        int  actionType;     //nada = 0, pulando=-1 atacando=1
        void stopMoving();
        LifeBarSplash lifeBar;
    //Metodos de ações publicos
    public:
        void moveLeft();
        void moveRight();
        void moveStop();
        void jump(bool not_jumping);
        void attack(int type_tiro);
        bool canSee(GameObject* obj, float distance);
        void takeDamage(int dano,int r = 255, int g = 255, int b = 10);
        bool canJump();

        int HPMax;
        int HP;

        virtual void onDead();
    //valores carregados
        float jump_speed;
        unsigned int jump_hold;

     //Atributos da entidade
    protected:

        int atk; //futuramente influenciará atk do player também
        bool isThrowed; //caso esteja sendo jogado, velocidade de stopMoving e andar eh reduzida em 90% até atingir o chão
        bool flip;
        int paralizeTime;
        bool isParalized;
        Timer timerParalized;

    //Getter and setters
    public:
        int getHP();
        int getHPMax();
        void setHP(int hp);
        void setHPMax(int hpmax);
        int getAtk();
        void setAtk(int atkPower);
        void setThrowed(bool throwing);
        void paralize(int paralizeTime);
};
