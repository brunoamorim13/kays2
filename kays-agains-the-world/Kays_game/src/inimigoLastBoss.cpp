#include "inimigo.h"
#include <iostream>

#include <math.h>

using namespace std;
InimigoLastBoss::InimigoLastBoss() : InimigoBase::InimigoBase()
{
    srand(time(NULL));

    walking_aceleration = 384;
    stop_aceleration = 704;

    flags |= ENTIDADE_FLAG_BOSS;

    atk = 1;

//    HP = HPMax = 40;
    HP = HPMax = 10;
    typeInimigo = 0;
    timerTeleporte.start();
    timerAtira.start();
    timerSpawn.start();

    size_ent = -1;

    tiro = new Tiro();
    tiro->setDamage(1);
    tiro->setSprite(SpriteManager::SpriteControl.getSprite(SPRITE_BALL), 32,32);
    actionMovement = ACT_NONE;
    actionType = BOSS_WAIT_L;
}

InimigoLastBoss::~InimigoLastBoss(){
    if(tiro) delete tiro;
}
void InimigoLastBoss::update(unsigned int dt){
    if(dead == false){
        onAI();
    }
    if(dead == true){
        an.update(dt);
    }
    Personagem::update(dt);
}
void InimigoLastBoss::render(){
    if(dead == true){
        an.render(pos.x - Camera::CameraControl.getX(), pos.y - Camera::CameraControl.getY());
    }
    Personagem::render();

}
void InimigoLastBoss::onDead()
{
    if(dead == false){
        //Menos 5 em y para diferenciar dano final
        TextSplash* t = new TextSplash(pos.x, pos.y-10, 0,0,80, "I'm Dead x.x!!!");
        t->addLists();

        an.setFrames(14+an.getFrameX()%2, 11, 100, true);
        SDLBase::sfx.playSfx(PLAY_SFX_MORTEBOSS);
        dead = true;
    }


    if(an.isReady())
    {
        //AnimationSplash(Animation anim, float x, float y, int loop = 1);  sprite morrendo.

        int type =  (rand()%4); //gera 0-1
        float chance = (rand()%10001);//gera 0-10001 e divide por 10001... 0.1 = 10%
        chance /=10001;//gera 0-100 e divide por 100... 0.1 = 10%
        int qtd;
        ///CHANCES DE OBTER OS ITENS
        if( chance < 0.1) { //10% de chance de dar item level 3
            qtd = 30+(rand()%20);
        } else if (chance < 0.4) { //40-10 = 30% de chance de dar item lv 2
            qtd = 5+(rand()%25);
        } else { // 100-40 = 60% de item lv 1
            qtd = (rand()%5)+1;
        }
        ItemObject* item = new ItemObject(pos,(ItemType)type,qtd);
        float dir = 80;
        dir += rand()%21; //adiciona 0-20, dir = 80-100;
        item->setDirecao(dir,150);
        item->maxVel.y = g_velMax_y;
        item->addLists();

        cout << "DEAD" << endl;
        Quest::QuestList[4]->addQtd(1);
    ///TESTES QUEST


        removeFromEntidadeList();
        delete (this);
    }

}


void InimigoLastBoss::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        Personagem* colidido = (Personagem*)entidadeColidida[i];

        if(actionType == BOSS_SUMMON)
        {
            timer[0].start();
            actionType = BOSS_ATK;
            timerEsperaAtirar.start();

        }


        if ( colidido->flags & ENTIDADE_FLAG_PLAYER){
//            //colidido->takeDamage(atk);
//            if(colidido->isInvencible() == false){
//                colidido->vel.x > 0 ? colidido->vel.x = -300 : colidido->vel.x = 300;
//                colidido->vel.y = -200;
//                colidido->setThrowed(true);
//                colidido->setInvencible(500);
//            }
        }
    }

    entidadeColidida.clear();
}
//Verica que ação deve ser executado pelo inimigo.
void InimigoLastBoss::onAI(){
    if( canSee(&Player::PlayerControl, 1000) ){
        int dir = Player::PlayerControl.pos.x > this->pos.x ? 0 : 1;

        if(actionType == BOSS_WAIT_L) {
            an.setFrames(3,6,150,false);
        } else
        if(actionType == BOSS_WAIT_R) {
            an.setFrames(2,6,150,false);
        }

    //Inicia animação de teleporte
        if(timerTeleporte.getTime() > 3000){
            actionType = BOSS_TELEPORTE;
            an.setFrames(8+dir,6,150,true);
            an.continueAnimation(0);
            timerTeleporte.stop();
        }
    //Terminou de se desfazer, começa a refazer
        if(actionType == BOSS_TELEPORTE && an.isReady()){
            ///POSICAO
            setInvencible(-1); //invencivel

            bool isValid = false;
            while(isValid == false){
                int rX = ( rand() % Map::MapControl.map_width )-2;
                int rY = 2 + ( rand() % (Map::MapControl.map_height-2) );

                if(isValidTile(Map::MapControl.getTileFromIndex(rX,rY) ) &&
                    Map::MapControl.getTileFromIndex(rX,rY)->tipo != TILE_TIPO_PLATAFORMA  &&
                   Map::MapControl.getTileFromIndex(rX,rY)->tipo != TILE_TIPO_SPIKE )
                    if(isValidTile(Map::MapControl.getTileFromIndex(rX+1,rY) ) &&
                        Map::MapControl.getTileFromIndex(rX+1,rY)->tipo != TILE_TIPO_PLATAFORMA &&
                        Map::MapControl.getTileFromIndex(rX+1,rY)->tipo != TILE_TIPO_SPIKE)
                        if(isValidTile(Map::MapControl.getTileFromIndex(rX+1,rY+1) ) &&
                            Map::MapControl.getTileFromIndex(rX+1,rY+1)->tipo != TILE_TIPO_PLATAFORMA &&
                            Map::MapControl.getTileFromIndex(rX+1,rY+1)->tipo != TILE_TIPO_SPIKE)
                            if(isValidTile(Map::MapControl.getTileFromIndex(rX+2,rY+1) ) &&
                                Map::MapControl.getTileFromIndex(rX+2,rY+1)->tipo != TILE_TIPO_PLATAFORMA &&
                                Map::MapControl.getTileFromIndex(rX+2,rY+1)->tipo != TILE_TIPO_SPIKE)
                            if(isValidTile(Map::MapControl.getTileFromIndex(rX,rY+1))  &&
                                Map::MapControl.getTileFromIndex(rX,rY+1)->tipo != TILE_TIPO_PLATAFORMA &&
                                Map::MapControl.getTileFromIndex(rX,rY+1)->tipo != TILE_TIPO_SPIKE )
                                if(Map::MapControl.getTileFromIndex(rX,rY+2)->tipo == TILE_TIPO_PLATAFORMA  || isValidTile(Map::MapControl.getTileFromIndex(rX,rY+2)) == false  )
                                if(Map::MapControl.getTileFromIndex(rX+1,rY+2)->tipo == TILE_TIPO_PLATAFORMA  || isValidTile(Map::MapControl.getTileFromIndex(rX+1,rY+2)) == false  )
                                if(Player::PlayerControl.isColisaoRetangulo(rX*TILE_SIZE, rY*TILE_SIZE, TILE_SIZE*2, TILE_SIZE*2) == false )
                                {
                                   setPos(rX*TILE_SIZE-11,rY*TILE_SIZE-11);
                                   if( canSee(&Player::PlayerControl, 500) )
                                        isValid = true;
                                }





            }

            actionType = BOSS_UN_TELEPORTE;
            an.setFrames(10+dir,6,150,true);
            an.continueAnimation(0);
            timerSpawn.start();
        }
    //Terminou de teleportar, Sumona inimigos
        if(actionType == BOSS_UN_TELEPORTE && an.isReady() && timerSpawn.getTime() > 1000) {
            setInvencible(0); // vencível
            timer[2].start();
            an.setFrames(6+dir,11,150,true);
            an.continueAnimation(0);
            timerSpawn.stop();

            actionType = BOSS_SUMMON;
        }

        //Termina sumonamento e volta a atirar
        if(actionType == BOSS_SUMMON)
        {
            if(an.isReady()) {
                spawnEnemy();
                timer[0].start();
                actionType = BOSS_ATK;
                timerEsperaAtirar.start();
            }

        }
    //Esperou, agora charge
        if(actionType == BOSS_ATK && timerEsperaAtirar.getTime() > 2000){
            actionType = BOSS_CHARGE;
            an.setFrames(4+dir,7,150,true);
            an.continueAnimation(0);
            timer[0].stop();
            timer[1].start();
            timerAtira.start();
            timerEsperaAtirar.stop();
        }
    //Terminou charge, começa ATIRAR
        if(actionType == BOSS_CHARGE && an.isReady()){
            an.setFrames(4 + dir,5,150,true);
            an.continueAnimation(0);

            timerAtira.start();
            atira();
        }
    //Termina de atirar, descarrega
        if(actionType == BOSS_CHARGE && timer[1].getTime() > 3500){
            actionType = BOSS_UNCHARGE;
            timer[1].stop();
        }
    //Termina de descarregar, espera e teleporta.
        if(actionType == BOSS_UNCHARGE && an.isReady()) {
            timerTeleporte.start();

            //Vira para player
            if(Player::PlayerControl.pos.x > this->pos.x){
                actionType = BOSS_WAIT_R;
            }
            if(Player::PlayerControl.pos.x < this->pos.x){
                actionType = BOSS_WAIT_L;
            }
        }


    } else {
    }
}

void InimigoLastBoss::atira(){


    Tiro* t = new Tiro(*tiro);

    t->elemento = TIRO_FLAG_FOGO;

    t->setFrames(ACT_RIGHT, 1);
    float dir = atan2(pos.y - Player::PlayerControl.pos.y, Player::PlayerControl.pos.x - pos.x )*180/M_PI;
    t->setDirecao(dir,300);
    t->setTempo(1400);
    t->setDamage(1);
    t->setPos(pos.x+16, pos.y);
    t->flags = ENTIDADE_FLAG_TIRO_INIMIGO | ENTIDADE_FLAG_MAP_ONLY_COLIDE | ENTIDADE_FLAG_COLIDE_ONLY;
    t->elemento = TIRO_FLAG_GHOST;
    t->addToTiroList();


    timerAtira.start();
}
#define TOTAL_ENEMIES 5
void InimigoLastBoss::spawnEnemy(){
    if ( canSee(&Player::PlayerControl, 1200) ){

        //Se tiver 2 inimigos a menos doq a ultima vez, spawna +2
        if ( size_ent != -1 && (int) Entidade::EntidadeList.size() >= 4 + TOTAL_ENEMIES  )
        {
            return;
        }
        {

            ///TEMP
            size_ent = Entidade::EntidadeList.size()+1;
            cout << Entidade::EntidadeList.size()+1 << endl;

            int sp_n = rand()%2; //0-1
            InimigoBase* temp = new InimigoBase();
            int size;
            sp_n == 0 ? size = 64 : size = 64;


            temp->setPos(this->pos.x, this->pos.y+10);
            temp->maxVel.x = (50+(rand()%50));
            if(sp_n == 1){
                    temp->setSprite(SpriteManager::SpriteControl.getSprite(17), size, size,0,0, size, size-2 );
                    temp->typeInimigo = 17;
                }
            else
                temp->setSprite(SpriteManager::SpriteControl.getSprite(2), size, size);
            temp->setAnimation(300,6);
            temp->addToEntidadeList();
        }
        timerSpawn.start();
    }
}

void InimigoLastBoss::setTimerDead(unsigned int tDead)
{
    tempoDead = tDead;
    timerDead.start();
}
