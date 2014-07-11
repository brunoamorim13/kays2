#include "player.h"
#include <iostream>

using namespace std;


Player Player::PlayerControl;


Player::Player() : Personagem::Personagem()
{
    HP = HPMax = 3;
    fogo = agua = terra = ar = 0;
    fogoMax = aguaMax = terraMax = arMax = 100;
    flags |= ENTIDADE_FLAG_PLAYER;
    srand(time(NULL));
    tiroTimerRandom.start();
    tiroTimerTodos.start();
    canShot = true;
    txtTimer.start();
    tiroGelo.start();
    tiroFogo.start();

    showCollision = false;
    type_tiro = ENERGY_TYPE_NONE;
}
void Player::resetPlayer(){

    HP = HPMax = 3;
    fogo = agua = terra = ar = 0;

    vel.x = vel.y = acel.x = acel.y;
    actionMovement = ACT_STOPPING;
    tiroTimerRandom.start();
    tiroTimerTodos.start();
    tiroGelo.start();
    tiroFogo.start();
    morte.stop();
    dead = false;
}
Player::Player(float x, float y) : Personagem::Personagem(x,y){
    HP = 3;
    fogo = agua = terra = ar = 0;
    HPMax = fogoMax = aguaMax = terraMax = arMax = 100;
    flags |= ENTIDADE_FLAG_PLAYER;
    srand(time(NULL));
    tiroTimerRandom.start();
    tiroTimerTodos.start();
    tiroFogo.start();
    tiroGelo.start();
    canShot = true;
    txtTimer.start();
}

void Player::update(unsigned int dt){

    if(HP==0){
        morte.start();
    }


    if(dead == true){
        an.update(dt);
    }


    if(type_tiro != ENERGY_TYPE_NONE)
    {
        if(an.isLoop() == true){
            type_tiro = ENERGY_TYPE_NONE;
        }
        else
        if(an.getFrameY() >= 5 ){
            execute_tiros();
        }
    }



    Personagem::update(dt);
    checkTeleports();
}

void Player::addEnergy(int type, int quantidade)
{
    int r=0,g=0,b=0;
    switch(type)
    {
        case 0:
            fogo += quantidade;
            if(fogo > fogoMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (fogo-fogoMax);
                fogo = fogoMax;
            }
            r = 200;g=50;b=25;
            break;
        case 1:
            terra += quantidade;
            if(terra > terraMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (terra-terraMax);
                terra = terraMax;
            }
            r = 50;g = 255;b = 50;
            break;
        case 2:
            agua += quantidade;
            if(agua > aguaMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (agua-aguaMax);
                agua = aguaMax;
            }
            b = 255;
            break;
        case 3:
            ar += quantidade;
            if(ar > arMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (ar-arMax);
                ar = arMax;
            }
            r= 255;b = 255; g = 255;
            break;
        case 4:
            HP += quantidade;
            if(HP > fogoMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (HP-HPMax);
                HP = HPMax;
            }
            r = 255;g=0;b=0;
            break;
    }

    TextSplash* t = new TextSplash(pos.x, pos.y, r, g,b, "+%d!", quantidade );
    t->addLists();
    ///TESTES
    Quest::QuestList[2]->addQtd(1);
}

void Player::handle_events()
{

    if(dead) return;



    if(InputManager::getInstance()->isKeyPressed(SDLK_RIGHT) || InputManager::getInstance()->getDirectionX() == 0){
        moveRight();
    }
    else
    if(InputManager::getInstance()->isKeyPressed(SDLK_LEFT) || InputManager::getInstance()->getDirectionX() == 1)
        moveLeft();
    else
        actionMovement = ACT_STOPPING;

    //Verifica tiros
    handle_tiros();


    ///JUMP
    if(InputManager::getInstance()->isKeyDown(SDLK_SPACE) || InputManager::getInstance()->isKeyDown(SDLK_z)  || InputManager::getInstance()->getDirectionY() == 0) {
        if(canDoJump) SDLBase::sfx.playSfx(PLAY_SFX_JUMP);
        jump(true);
    }

   if(InputManager::getInstance()->isKeyPressed(SDLK_SPACE) || InputManager::getInstance()->isKeyPressed(SDLK_z) || InputManager::getInstance()->getDirectionY() == 0)
        jump(false);
    else
        jumpTimer.stop();
    ///END JUMP
}

void Player::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        if(colVel.y > 0) //Se estava indo para baixo quando colidiu.
           ; //this->extVel.x = entidadeColidida[i]->vel.x;
    }

    entidadeColidida.clear();
}

void Player::execute_tiros()
{
//    if( type_tiro == ENERGY_TYPE_AR) {
//        ar-= 1;
//
//        float dir=0;
//        int posX = this->pos.x;
//        //int posY = this->pos.y + 9; Topo do cajado
//        int posY = this->pos.y + 18;
//        Tiro* t = new Tiro();
//
//        int variacao = rand() % 31;  //vai de 0-30
//        t->setSprite(spr_tiroAr, 20,10);
//
//        if(this->an.getFrameX() == ACT_TYPE_ATTACK) {
//            posX += 20;
//            dir = variacao-15;
//            t->setFrames(ACT_RIGHT, 1);
//        }
//        else if(this->an.getFrameX() == ACT_TYPE_ATTACK+1){
//            dir = 165+variacao;
//            posX -=10;
//            t->setFrames(ACT_LEFT, 1);
//        }
//        t->setDirecao(dir,500);
//        t->setDamage(3);
//        t->setTempo(500);
//        t->setPos(posX, posY);
//        t->addToTiroList();
//        SDLBase::sfx.playSfx(PLAY_SFX_SHOT1);
//    }
//    else
    //Tiro normal?
    if(type_tiro == ENERGY_TYPE_NORMAL) {

        float dir=0;
        int posX = this->pos.x;
        //int posY = this->pos.y + 9; Topo do cajado
        int posY = this->pos.y + 18;
        Tiro* t = new Tiro();

        t->setSprite(spr_tiroComum, 13,13);

        if(this->an.getFrameX() == ACT_TYPE_ATTACK) {
            posX += 20;
            dir = 0;
            t->setFrames(ACT_RIGHT, 7, 100);
        }
        else if(this->an.getFrameX() == ACT_TYPE_ATTACK+1){
            dir = 180;
            posX -=10;
            t->setFrames(ACT_LEFT,7,100);
        }
        t->setDirecao(dir,300);
        t->setDamage(0);
        t->setTempo(1500);
        t->setPos(posX, posY);
        t->addToTiroList();
        SDLBase::sfx.playSfx(PLAY_SFX_STUN);
    }
    else
    //Tiro perfurante/acido
    if(type_tiro == ENERGY_TYPE_AGUA && agua >= 5 && tiroGelo.getTime() >= 1500) {

        //agua-= 5;

        tiroGelo.start();

        float dir=0;
        int posX = this->pos.x;
        int posY = this->pos.y + 18;
        Tiro* t = new Tiro();
         t->setSprite(spr_tiroGelo, 24,10);

        if(this->an.getFrameX() == ACT_TYPE_ATTACK) {
            posX += 20;
            dir = 0;
            t->setFrames(ACT_RIGHT, 4,100);
        }
        else if(this->an.getFrameX() == ACT_TYPE_ATTACK+1){
            dir = 180;
            posX -=10;
            t->setFrames(ACT_LEFT, 4, 100);
        }
        t->setDirecao(dir,500);
        t->elemento = TIRO_FLAG_AGUA;
        t->setDamage(1);
        t->setTempo(800);
        t->setPos(posX, posY);
        t->addToTiroList();
        t->setPiercing(true);
        SDLBase::sfx.playSfx(PLAY_SFX_GELO);
    }
    else
    //Shotgun -> 3 fire
    if(type_tiro == ENERGY_TYPE_FOGO && fogo >= 3 && tiroFogo.getTime() >= 3000) {

        //fogo-= 3;

        tiroFogo.start();

        for(int i = 0; i < 5; i++)
        {
            float dir=0;
            int posX = this->pos.x;
            //int posY = this->pos.y + 9; Topo do cajado
            int posY = this->pos.y + 18;
            Tiro* t = new Tiro();
            t->setSprite(spr_tiroFogo, 28,10);

            if(this->an.getFrameX() == ACT_TYPE_ATTACK) {
                posX += 20;
                dir = i*10-20;
                 t->setFrames(ACT_RIGHT, 4,100);
            }
            else if(this->an.getFrameX() == ACT_TYPE_ATTACK+1){
                dir = 160+i*10;
                posX -=10;
                 t->setFrames(ACT_LEFT, 4,100);
            }
            t->setDirecao(dir,450);
            t->elemento = TIRO_FLAG_FOGO;
            t->setDamage(3);
            t->setTempo(700);
            t->setPos(posX, posY);
            t->addToTiroList();
        }

        SDLBase::sfx.playSfx(PLAY_SFX_FOGO);

    }
    else
    //Tiro rasteiro
    if(type_tiro == ENERGY_TYPE_TERRA) {
        //terra-= 1;

        float dir=0;
        int posX = this->pos.x;
        int posY = this->pos.y + 18;
        Tiro* t = new Tiro();
        t->setSprite(spr_tiroTerra, 20,10);

        if(this->an.getFrameX() == ACT_TYPE_ATTACK) {
            posX += 20;
            dir = -30;
            t->setFrames(ACT_RIGHT, 1);
        }
        else if(this->an.getFrameX() == ACT_TYPE_ATTACK+1){
            dir = 180+30;
            posX -=10;
            t->setFrames(ACT_LEFT, 1);
        }
        t->setDirecao(dir,300);
        t->setDamage(1);
        t->setTempo(2000);
        t->setPos(posX, posY);
        t->elemento = TIRO_FLAG_TERRA;
        t->addToTiroList();

        SDLBase::sfx.playSfx(PLAY_SFX_STUN);
    }

    type_tiro = ENERGY_TYPE_NONE;

}

void Player::handle_tiros()
{
    if(type_tiro != ENERGY_TYPE_NONE) return;
    if(canShot == false) return;
//Tiro random, atira mais rapido doq os outros
//    if(InputManager::getInstance()->isKeyPressed(SDLK_f)) {
//        type_tiro = ENERGY_TYPE_AR;
//        if(tiroTimerRandom.getTime() > 80)
//        {
//
//            tiroTimerTodos.start();
//            tiroTimerRandom.start();
//            if(ar < 1) {
//                if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto
//                txtTimer.start();
//
//                TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
//                t->addLists();
//                TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 1 ar.");
//                t2->addLists();
//                return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
//            }
//
//        } ///FIM DO TIRO 'S'
//        attack();
//        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
//    }
/// Só podem atirar 1 vez a kd 150ms
    if(tiroTimerTodos.getTime() < 150) return; // limita 1 tira para cada 150ms

    //Tiro normal?
    if(InputManager::getInstance()->isKeyDown(SDLK_a) || InputManager::getInstance()->isJoyButtonDown(0)) {
        type_tiro = ENERGY_TYPE_NORMAL;
        tiroTimerTodos.start();
        attack(type_tiro);

    }

    //Tiro perfurante/acido
    if(InputManager::getInstance()->isKeyDown(SDLK_s) || InputManager::getInstance()->isJoyButtonDown(3)) {

        type_tiro = ENERGY_TYPE_AGUA;

        tiroTimerTodos.start();
        tiroTimerRandom.start();
        if(agua < 5  && tiroGelo.getTime() < 1500) {
            //if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto

//            TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
//            t->addLists();
//            TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 5 agua.");
//            t2->addLists();
//            txtTimer.start();
            return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
        }

        attack(type_tiro);

        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
    }

    //Shotgun -> 3 fire
    if(InputManager::getInstance()->isKeyDown(SDLK_d) || InputManager::getInstance()->isJoyButtonDown(2)) {
        type_tiro = ENERGY_TYPE_FOGO;
        tiroTimerTodos.start();

        if(fogo < 3 && tiroFogo.getTime() < 3000) {
            //if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto
//            txtTimer.start();
//            TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
//            t->addLists();
//            TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 3 fogo.");
//            t2->addLists();
            return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
        }


        attack(type_tiro);

        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.

    }

}

// Verifica se o player colidiu com o teleporte, e muda o mapa------------
void Player::checkTeleports()
{
    for(unsigned int i = 0; i < Teleporte::TeleporteList.size();i++)
    {
        Teleporte::TeleporteList[i]->update(this);
    }
}

int Player::getFogo() { return fogo; }
int Player::getAgua() { return agua; }
int Player::getAr() { return ar; }
int Player::getTerra() { return terra; }

int Player::getFogoMax() { return fogoMax; }
int Player::getAguaMax() { return aguaMax; }
int Player::getArMax() { return arMax; }
int Player::getTerraMax() { return terraMax; }

void Player::setFogo(int fire){fogo = fire;}
void Player::setAgua(int water){agua = water;}
void Player::setAr(int air){ar = air;}
void Player::setTerra(int earth){terra = earth;}

void Player::setFogoMax(int firemax){fogoMax = firemax;}
void Player::setAguaMax(int watermax){aguaMax = watermax;}
void Player::setArMax(int airmax){arMax = airmax;}
void Player::setTerraMax(int earthmax){terraMax = earthmax;}
