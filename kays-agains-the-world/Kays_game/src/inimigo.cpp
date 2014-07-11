#include "inimigo.h"



InimigoBase::InimigoBase() : Personagem::Personagem()
{
    srand(time(NULL));

    walking_aceleration = 32;
    stop_aceleration = 32;

    atk = 1;

    tiroTimer.start();

    HP = HPMax = 3;
    typeInimigo = 0;

    flags |= ENTIDADE_FLAG_INIMIGO;
    //Só colide com mapa mas propaga colisões
    flags |= ENTIDADE_FLAG_MAP_ONLY_COLIDE;

    //jumpjump_speed = 300;
    jump_speed = 350;

    for(int i = 0; i < TIMERS_N; i++)
        timer[i].stop();
    for(int i = 0; i < VAR_BOOL_N; i++)
        var[i] = false;
}
void InimigoBase::update(unsigned int dt){
    if(dead == false && !isParalized){
        onAI();
    }
    if(dead == true){
        isParalized = false;
        an.update(dt);
    }




    if(isParalized){
        an.setFrames(6+an.getFrameX()%2,4,100,false);
        tiroTimer.pause();
        stopParalize.start();
        invencible = false;


    }
    if(stopParalize.getTime()>300){
        tiroTimer.unpause();


    }


    if(typeInimigo==1 && timer[1].getTime() > 100){
            an.setFrames(10+an.getFrameX()%2, 5,150, false);
            an.update(dt);
    }

    if(typeInimigo==17 && timer[1].getTime() > 100){
            an.setFrames(10+an.getFrameX()%2, 5,150, false);
            an.update(dt);
    }

    if(typeInimigo==0 && timer[1].getTime() > 100){
        an.setFrames(10+an.getFrameX()%2, 6,200, false);
        an.update(dt);
    }



    hitWall = false;
    Personagem::update(dt);
}
void InimigoBase::render(){
    if(dead == true){
        an.setFrames(8+an.getFrameX()%2, 7, 100, true);
        an.render(pos.x - Camera::CameraControl.getX(), pos.y - Camera::CameraControl.getY());
    }
    Personagem::render();

}
void InimigoBase::onDead()
{
    if(dead == false){
        //Menos 5 em y para diferenciar dano final
        TextSplash* t = new TextSplash(pos.x, pos.y-10, 0,0,80, "I'm Dead x.x!!!");
        t->addLists();
        int anFrame = an.getFrameX();
        if(anFrame == 0 || anFrame == 4 || anFrame == 5 )
            an.setFrames(2, 1, 100, true);
        else
            an.setFrames(3, 1, 100, true);
        //an.continueAnimation(0);
        if(typeInimigo == 0 || typeInimigo == 17){
            SDLBase::sfx.playSfx(PLAY_SFX_MORTEMAGO);
        }else if(typeInimigo == 1)
            SDLBase::sfx.playSfx(PLAY_SFX_MORTEMERCENARIO);

        dead = true;
    }


    if(an.isReady())
    {
        removeFromEntidadeList();
        delete (this);
    }

}


void InimigoBase::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        Personagem* colidido = (Personagem*)entidadeColidida[i];

        if(colidido->isFlag(ENTIDADE_FLAG_INIMIGO)){
            if(colVel.y > 0) //Se estava indo para baixo quando colidiu.
                this->extVel.x = entidadeColidida[i]->vel.x;
        }
    }

    entidadeColidida.clear();
}
//Verica que ação deve ser executado pelo inimigo.
void InimigoBase::onAI(){
    if( canSee(&Player::PlayerControl, 400) ){

        if(hitWall){
            jump(true);
        }

        //Quando finalizar a animação, muda para corrida, e liga novo timer.
        if(an.isReady() && var[0] == true){
            an.setFrames(2+an.getFrameX()+1,8,an.getDelay(),false);
            lastMaxVel.x = maxVel.x;
            maxVel.x = maxVel.x*6;
            timer[0].start();

            if(an.getFrameX() == 5) {
                actionMovement = ACT_RIGHT;
            } else {
                actionMovement = ACT_LEFT;
            }
        }




        if(typeInimigo == 0 && timer[1].getTime() > 400){
            attackMelee();
            timer[1].stop();
            timer[2].start();
            an.setFrames(2+an.getFrameX()%2, 8, 100, false);
        } else
        //Faz esperar parado por algum tempo
        if(timer[1].getTime() > 500){
            attackShot();
            timer[1].stop();
            timer[2].start();
            an.setFrames(2+an.getFrameX()%2, 8, 100, false);
        }else

        if(typeInimigo == 2 && timer[1].getTime() > 100){

            attackMelee();
            timer[1].stop();
            timer[2].start();
        }
        if( timer[1].is_started() ) {
            moveStop();
            return;
        }
        //Espera a MAIS para o proximo rage
        if(timer[2].getTime() > 3500){
            timer[2].stop();
        }

        ///SHOT
        if( canSee(&Player::PlayerControl, 350) && typeInimigo != 0 && timer[2].is_started() == false) {

            if(tiroTimer.getTime()> 1500){
                timer[1].start();
            }

        }


        ///MELEE ATTACK
        if( canSee(&Player::PlayerControl, 50) && typeInimigo == 0 && timer[2].is_started() == false) {

            if(tiroTimer.getTime()> 1000){
                timer[1].start();
            }

        }



        if(Player::PlayerControl.pos.x > this->pos.x+50){
            moveRight();
        }else
        if(Player::PlayerControl.pos.x < this->pos.x-50){
            moveLeft();
        }else
        {
            moveStop();
        }


    } else { // Se não puder ver player na tela, para
        moveStop();
    }
}
void InimigoBase::attackShot()
{
    tiroTimer.start();
    float dir=0;
    int posX = this->pos.x+20;
    //int posY = this->pos.y + 9; Topo do cajado
    int posY = this->pos.y + 15;
     Tiro* t = new Tiro();

    t->flags = ENTIDADE_FLAG_TIRO_INIMIGO ;
    t->elemento = TIRO_FLAG_FOGO;

    if(typeInimigo == 17){
        t->setSprite(Player::PlayerControl.spr_tiroFogo, 28,10);
    }else if(typeInimigo == 1){
        t->setSprite(Player::PlayerControl.spr_tiroGelo, 24,10);
    }


    if(this->an.getFrameX()%2 == 0) {
        posX += 20;
        dir = 0;
        t->setFrames(ACT_RIGHT, 4, 100);
    }
    else if(this->an.getFrameX()%2 == 1){
        dir = 180;
        posX -=10;
        t->setFrames(ACT_LEFT,4,100);
    }

    t->setDirecao(dir,300);
    t->setDamage(1);
    t->setTempo(1000);
    t->setPos(posX, posY);
    t->addToTiroList();

    if(typeInimigo == 17){
        SDLBase::sfx.playSfx(PLAY_SFX_FOGO);
    }else if(typeInimigo == 1){
        SDLBase::sfx.playSfx(PLAY_SFX_GELO);
    }

}
void InimigoBase::attackMelee()
{
    tiroTimer.start();

    float dir=0;
    int posX = this->pos.x+20;
    //int posY = this->pos.y + 9; Topo do cajado
    int posY = this->pos.y + 18;
     Tiro* t = new Tiro();

    t->flags = ENTIDADE_FLAG_TIRO_INIMIGO ;
    t->elemento = TIRO_FLAG_AR;

    t->setSprite(Player::PlayerControl.spr_tiroAr, 30,40);

    if(this->an.getFrameX()%2 == 0) {
        posX += 20;
        dir = 0;
        t->setFrames(ACT_RIGHT, 4, 40);
    }
    else if(this->an.getFrameX()%2 == 1){
        dir = 180;
        posX -=30;
        t->setFrames(ACT_LEFT,4,40);
    }

    t->setDirecao(dir,300);
    t->setDamage(1);
    t->maxVel.x=0;
    t->setTempo(100);
    t->setPos(posX, posY);
    t->addToTiroList();
    SDLBase::sfx.playSfx(PLAY_SFX_MELEE);
}

void InimigoBase::onNotValidPosition(bool isX){
    if(isX) {
        vel.x = 0;
        //Se não tiver colidido com entidades, bateu na parede
        //if(entidadeColidida.empty())
            hitWall = true;
    }
    else
        vel.y = 0;
}
