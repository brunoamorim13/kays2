#include "tiro.h"

std::vector<Tiro*> Tiro::TiroList;

Tiro::Tiro() : Entidade() {
    flags = ENTIDADE_FLAG_TIRO_PLAYER | ENTIDADE_FLAG_MAP_ONLY_COLIDE;
    elemento = TIRO_FLAG_COMUM;
    damage = 0;
    showCollision = false;
    tiroTimer.start();
    damageTimer.start();
    piercing = false;
    delayDano = 30;
    first = true;
}

Tiro::Tiro(float graus, float velocidade, eEntFlag flagTiro, eTiroElemento flagElemento) : Entidade() {
    flags = flagTiro;
    elemento = flagElemento;
    damage = 0;
    setDirecao(graus, velocidade);
    maxVel.x = maxVel.y = velocidade;
    tiroTimer.start();
    damageTimer.start();
    showCollision = false;
    piercing = false;
    delayDano = 30;
    first = true;
    elemento = TIRO_FLAG_COMUM;
}
//Remove entidade da lista de tiros ---------------------
void Tiro::removeFromTiroList()
{
    for(unsigned int i = 0; i < TiroList.size(); i++)
    {
        if (TiroList[i] == this)
            TiroList.erase(TiroList.begin()+i);
    }
}
//Add tiro para a lista de tiros ---------------------
void Tiro::addToTiroList()
{
    for(unsigned int i = 0; i < TiroList.size(); i++)
    {
        if (TiroList[i] == this)
            return;
    }

    TiroList.push_back(this);
}

void Tiro::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        Personagem* colidido = (Personagem*)entidadeColidida[i];
        int red = 254, green=0, blue=0;
        if (colidido->flags & ENTIDADE_FLAG_PLAYER) {
            red = green = 255; blue = 10;
        }
        if(damageTimer.getTime() > delayDano || first  ){
            damageTimer.start();
            if(this->elemento == TIRO_FLAG_COMUM)
            {
                colidido->takeDamage(0, red, green, blue);
                colidido->paralize(2500);
            }
            else
            {
                colidido->takeDamage(damage,red,green,blue);
                if(colidido->isInvencible() == false){
                    this->vel.x > 0 ? colidido->vel.x = 300 : colidido->vel.x = -300;
                    colidido->vel.y = -200;
                    colidido->setThrowed(true);
                    colidido->setInvencible(1000);
                }
            }
            first = false;
        }
        if(piercing == false)
            this->dead = true;
    }

    entidadeColidida.clear();
}

void Tiro::onNotValidPosition(bool isX){
    if(elemento & TIRO_FLAG_TERRA)
    {
        if(isX){
            dead = true;//explode
        }else{
            //vel.y = 0;
        }
    } else if( (elemento & TIRO_FLAG_GHOST) == TIRO_FLAG_GHOST)
    {

    }else
    {
        cout << elemento << endl;
        dead = true;
    }
}

bool Tiro::isColisaoEntidade(Entidade* objeto, int posX, int posY)
{

    //Não é o mesmo objeto e não é nulo
    //Não é morto
    // É colisão
    if(this != objeto && objeto != NULL && !objeto->dead &&
        (objeto->flags & ENTIDADE_FLAG_MAP_ONLY) != ENTIDADE_FLAG_MAP_ONLY  && (objeto->flags & ENTIDADE_FLAG_NPC) != ENTIDADE_FLAG_NPC &&
       objeto->isColisaoRetangulo(posX + col_offset.x, posY + col_offset.y, col_offset.w, col_offset.h))
       {
            //Se a entidade que atirou for do mesmo tipo, ignora a colisão;
           if(flags & ENTIDADE_FLAG_TIRO_PLAYER && objeto->flags & ENTIDADE_FLAG_PLAYER)
                return false;
           else if (flags & ENTIDADE_FLAG_TIRO_INIMIGO && objeto->flags & ENTIDADE_FLAG_INIMIGO )
                return false;

           setColisao(objeto);
           objeto->setColisao(this);
           return true;
       }
    return false;
}
void Tiro::update(unsigned int dt) {
    //Se já tiver decorrido o tempo do tiro.
    if((int)tiroTimer.getTime() > tempo) {
        dead = true;
    }
    if(dead) onExplode();
    Entidade::update(dt);

}
bool Tiro::onRampHitX(int newX, int newY){
    return false;

}
void Tiro::onExplode() {
    an.setFrames(an.getFrameX()+2, 6, 50);
    AnimationSplash* anSp = new AnimationSplash(an,pos.x, pos.y);
   // anSp->setSpeeds(vel, maxVel, acel,col_offset);
    anSp->addLists();

    removeFromTiroList();
    delete (this); //suicidio
}
void Tiro::setDamage(int dano) {
    damage = dano;
}
int Tiro::getDamage() {
    return damage;
}
void Tiro::setTempo(int msTempo){
    tempo = msTempo;
    tiroTimer.start();
 }

void Tiro::setPiercing(int pierce){
    piercing = pierce;
}

void Tiro::setDelayDano(unsigned int delay){
    delayDano = delay;
}
