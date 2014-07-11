#include "personagem.h"

Personagem::Personagem() : Entidade::Entidade(){
    canDoJump = false;
    actionMovement = actionType = ACT_STOPPING;
    jump_speed = jump_hold = 0;
    flags = ENTIDADE_FLAG_FISICA;
    HP = HPMax = 100;

    gravity_speed = g_gravidade;
    maxVel.y = g_velMax_y;
    lifeBar.setHP(&HP,&HPMax);
    lifeBar.setPos(&pos);
    Vetor vet(-1,-1);
    lifeBar.setPosOffset(vet);
    lifeBar.addLists();
    invencible = false;
    atk = 5;
    isThrowed = false;
    showCollision = false;
    isParalized = false;
    paralizeTime = 0;
    timerParalized.start();
}
Personagem::Personagem(float x, float y) : Entidade::Entidade(x,y){
    canDoJump = false;
    actionMovement = actionType = 0;
    jump_speed = jump_hold = 0;
    flags = ENTIDADE_FLAG_FISICA;
    HP = HPMax = 100;
    gravity_speed = g_gravidade;
    maxVel.y = g_velMax_y;
    lifeBar.setHP(&HP,&HPMax);
    lifeBar.setPos(&pos);
    Vetor vet(-1,-1);
    lifeBar.setPosOffset(vet);
    lifeBar.addLists();
    invencible = false;
    atk = 5;
    isThrowed = false;
    showCollision = false;
    timerParalized.start();
    isParalized = false;
    paralizeTime = 0;
}
Personagem::~Personagem(){
    lifeBar.removeFromDrawList();
    lifeBar.removeFromLoopList();
}
void Personagem::stopMoving(){
    if(vel.x == 0) {
        return;
    }
    if(vel.x > 0) {
		acel.x = -stop_aceleration;//-50;
		if(isThrowed) acel.x *=0.1;
	}

    // If moving left
	if(vel.x < 0) {
		acel.x =  stop_aceleration;//50;
		if(isThrowed)
            acel.x*= 0.1;
	}

    // se velocidade estiver entre 50pixels/s, para
	if(vel.x < 50.0f && vel.x > -50.0f) {

		acel.x = 0;
		vel.x = 0;
		if(an.isLoop() && actionMovement != ACT_NONE){ //Só para quando animação é loop, caso contrário irá parar sozinha.
            an.setFrames(2+an.getFrameX()%2,8,100,false);
         }
	}
}

void Personagem::takeDamage(int dano,int r, int g, int b) {
    if(invencible) return;
    TextSplash* damage = new TextSplash(pos.x, pos.y, r, g,b, "%d!", dano );
    damage->addLists();
    HP -= dano;

    if(this->isFlag(ENTIDADE_FLAG_PLAYER)){
        an.setFrames(6+an.getFrameX()%2, 4, 100, true);
        an.continueAnimation(0);
        SDLBase::sfx.playSfx(PLAY_SFX_DANO);
    }
    if(this->isFlag(ENTIDADE_FLAG_INIMIGO)){
        if(this->isFlag(ENTIDADE_FLAG_BOSS)){
            an.setFrames(12+an.getFrameX()%2, 4, 100, true);
            an.continueAnimation(0);

        }else{
            an.setFrames(4+an.getFrameX()%2, 4, 100, true);
            an.continueAnimation(0);
            if(!this->isParalized){
                //SDLBase::sfx.playSfx(PLAY_SFX_DANOINIMIGO);
            }
        }

    }



    if (HP < 0)   HP = 0;
    lifeBar.setDelay(1000);
}
void Personagem::render(){
    Entidade::render();
}

void Personagem::update(unsigned int dt){

    if(HP <= 0) {
        onDead();
        return;
    }
    if(dead) return;


    //Se decorrido o tempo, desparaliza
    if((int)timerParalized.getTime() > paralizeTime){
        isParalized = false;
    }
    //Senao, se paralizado, ignora movimentos
    else
    if(isParalized){
        return;
    }


    switch(actionMovement) {
        case ACT_LEFT:
            acel.x = -walking_aceleration;
            if(isThrowed) acel.x *= 0.1;
            break;
        case ACT_RIGHT:
            acel.x = walking_aceleration;
            if(isThrowed) acel.x *= 0.1;
            break;
        case ACT_STOPPING:
            stopMoving();
            break;
    }

    //Retorna para parado após executar ataque
    if(an.isReady() && actionType == ACT_TYPE_ATTACK) {
        an.setFrames(2+an.getFrameX()%2, an.getNFrames(), 100);
        actionType = ACT_TYPE_NONE;
    }

    if(actionType == ACT_TYPE_JUMP && vel.y == 0) {
        an.setFrames(2+an.getFrameX()%2, an.getNFrames(), 100);
        an.continueAnimation(0);
        actionType = ACT_TYPE_NONE;
    }


    if(timerInvencible.is_started() && timerInvencible.getTime() > tempoInvencible)
    {
        invencible = false;
        timerInvencible.stop();
    }

    Entidade::update(dt);
    if(canDoJump)//Se encostou no chão, para de ser jogado e anda normalmente.
        isThrowed = false;
}
void Personagem::moveLeft(){

    if(!isThrowed)
    an.setFrames(ACT_LEFT, an.getNFrames(), 100);

    if(vel.x > 0) {
        moveStop();
        return;
    }
    if(actionMovement == ACT_LEFT)
        return;
    //Só seta a posição da animação para 0 uma vez
    an.continueAnimation(0);
    actionMovement = ACT_LEFT;
}
void Personagem::moveRight(){

    if(!isThrowed)
    an.setFrames(ACT_RIGHT, an.getNFrames(), 100);

    if(vel.x < 0) {
        moveStop();
        return;
    }
    if(actionMovement == ACT_RIGHT)
        return;

    an.continueAnimation(0);
    actionMovement = ACT_RIGHT;
}
void Personagem::moveStop(){
    actionMovement = ACT_STOPPING;
}

void Personagem::jump(bool not_jumping){
    actionType = ACT_TYPE_JUMP;
    //Se não puder pular e dizer para pular, retorna
    if(!canDoJump && not_jumping)
        return;

    if(not_jumping)
    {
        vel.y = -jump_speed;
        canDoJump = false;
        jumpTimer.start();
        an.pauseAnimation(8);
    }
    else
    {
        if(jumpTimer.getTime() < jump_hold && jumpTimer.is_started())
        {
            vel.y = -jump_speed;
        }
    }

}
void Personagem::attack(int type_tiro){
    actionType = ACT_TYPE_ATTACK;
    if(type_tiro == 0)
         an.setFrames(ACT_TYPE_ATTACK+an.getFrameX()%2,8,75,true);
    else if(type_tiro == 2)
         an.setFrames(ACT_TYPE_ATTACK+an.getFrameX()%2,8,65,true);
    else
        an.setFrames(ACT_TYPE_ATTACK+an.getFrameX()%2,8,55,true);

    an.continueAnimation(0);

}

bool Personagem::canSee(GameObject* obj, float distance){

    Vetor centroArea(pos.x + an.getClip().w/2, pos.y + an.getClip().h/2);
    Vetor pontoColisao;

    //X mais proximo
    //Se a esquerda então ponto x mais proximo = x da caixa
    if(centroArea.x < obj->pos.x)
        pontoColisao.x = obj->pos.x;
    else if(centroArea.x > obj->pos.x + obj->col_offset.w) //Se direita x + w
        pontoColisao.x = obj->pos.x + obj->col_offset.w;
    else
        pontoColisao.x = centroArea.x; // senão, centro

    //Y mais proximo
    if(centroArea.y < obj->pos.y)
        pontoColisao.y = obj->pos.y;
    else if(centroArea.y > obj->pos.y + obj->col_offset.h)
        pontoColisao.y = obj->pos.y + obj->col_offset.h;
    else
        pontoColisao.y = centroArea.y;

    Vetor distancia = centroArea;
    distancia = distancia - pontoColisao;


    //Se a distancia entre o centro e ponto mais proximo for menor que alcance
    if ( distancia.lenght() < distance )
    {//colidiu
        return true;
    }
    return false;
}

bool Personagem::canJump(){
    return canDoJump;
}

int Personagem::getHP(){
    return HP;
}
int Personagem::getHPMax(){
    return HPMax;
}

void Personagem::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        if(colVel.y > 0) //Se estava indo para baixo quando colidiu.
            this->extVel.x = entidadeColidida[i]->vel.x;
    }

    entidadeColidida.clear();
}

void Personagem::onDead()
{

    if(dead==false){
        if(this->isFlag(ENTIDADE_FLAG_PLAYER)){
            an.setFrames(8+an.getFrameX()%2, 9, 100, true);
            SDLBase::sfx.playSfx(PLAY_SFX_MORTEKAYS);
        }


        if(this->isFlag(ENTIDADE_FLAG_INIMIGO)){
            if(this->isFlag(ENTIDADE_FLAG_BOSS)){
                an.setFrames(14+an.getFrameX()%2, 11, 200, true);
            }else{
                an.setFrames(8+an.getFrameX()%2, 9, 200, true);
            }

        }

         dead = true;

         actionMovement = actionType = 0;
    }

}


int Personagem::getAtk(){ return atk;}
void Personagem::setAtk(int atkPower) {
    if(atkPower >= 0)
        atk = atkPower;
}

void Personagem::setThrowed(bool throwing)
{
    isThrowed = throwing;
}

void Personagem::setHP(int hp){HP = hp;}
void Personagem::setHPMax(int hpmax){HPMax = hpmax;}

void Personagem::paralize(int paralizeTime)
{

    if(this->isFlag(ENTIDADE_FLAG_BOSS))
        return;

    isParalized = true;
    this->paralizeTime = paralizeTime;
    timerParalized.start();
//    cout << timerParalized.getTime() << endl;
}
