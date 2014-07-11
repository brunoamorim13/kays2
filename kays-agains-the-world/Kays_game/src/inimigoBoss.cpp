#include "inimigo.h"

InimigoBoss::InimigoBoss() : InimigoBase::InimigoBase()
{
    srand(time(NULL));

    walking_aceleration = 384;
    stop_aceleration = 704;

    atk = 35;

    HP = HPMax = 200;
    typeInimigo = 0;
    timerSpawn.start();

    size_ent = -1;
}
void InimigoBoss::update(unsigned int dt){
    if(dead == false){
        onAI();
    }
    if(dead == true){
        an.update(dt);
    }
    Personagem::update(dt);
}
void InimigoBoss::render(){
    if(dead == true){
        an.render(pos.x - Camera::CameraControl.getX(), pos.y - Camera::CameraControl.getY());
    }
    Personagem::render();

}
void InimigoBoss::onDead()
{
    if(dead == false){
        //Menos 5 em y para diferenciar dano final
        TextSplash* t = new TextSplash(pos.x, pos.y-10, 0,0,80, "I'm Dead x.x!!!");
        t->addLists();

        an.setFrames(an.getFrameX()+2, 12, 100, true);
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

    ///TESTES QUEST
        Quest::QuestList[3]->addQtd(1);

        removeFromEntidadeList();
        delete (this);
    }

}


void InimigoBoss::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        Personagem* colidido = (Personagem*)entidadeColidida[i];
        if ( colidido->flags & ENTIDADE_FLAG_PLAYER){
            colidido->takeDamage(atk);
            if(colidido->isInvencible() == false){
                colidido->vel.x > 0 ? colidido->vel.x = -300 : colidido->vel.x = 300;
                colidido->vel.y = -200;
                colidido->setThrowed(true);
                colidido->setInvencible(300);
            }
        }
    }

    entidadeColidida.clear();
}
//Verica que ação deve ser executado pelo inimigo.
void InimigoBoss::onAI(){
    if( canSee(&Player::PlayerControl, 500) ){

        if(timerSpawn.getTime() > 3000) {
            spawnEnemy();
        }

        if(Player::PlayerControl.pos.x > this->pos.x){
            moveRight();
        }
        if(Player::PlayerControl.pos.x < this->pos.x){
            moveLeft();
        }

    } else {
        actionMovement = ACT_STOPPING;
    }
}

void InimigoBoss::spawnEnemy(){
    if ( canSee(&Player::PlayerControl, 500) ){

        //Se tiver 2 inimigos a menos doq a ultima vez, spawna +2
        if ( size_ent != -1 && size_ent <= (int)(Entidade::EntidadeList.size()-1)  )
        {
            return;
        }
        {

            ///TEMP
            size_ent = Entidade::EntidadeList.size()-1;

            int sp_n = rand()%2; //0-1
            InimigoBase* temp = new InimigoBase();
            int size;
            sp_n == 0 ? size = 16 : size = 32;


            temp->setPos(this->pos.x, this->pos.y-32);
            temp->maxVel.x = (50+(rand()%50));
            if(sp_n == 1){
                    temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), size, size,0,0, size, size-2 );
                    temp->typeInimigo = 1;
                }
            else
                temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), size, size);
            temp->setAnimation(300,6);
            temp->addToEntidadeList();
        }
        timerSpawn.start();
    }
}
