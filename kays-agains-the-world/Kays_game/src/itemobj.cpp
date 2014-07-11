#include "itemobj.h"

Sprite* ItemObject::spr_itens;


ItemObject::ItemObject(Vetor posicao, ItemType itemType, int qtd) : Entidade::Entidade()
{
    setSprite(spr_itens, 16,16,0,0,16,16);
    this->itemType = itemType;
    an.setFrames(itemType);
    quantidade = qtd;

    pos.x = posicao.x;
    pos.y = posicao.y;

    //Escolhe qual o sprite baseado na quantidade.... para energias e power-ups.
    if(qtd >= 30)
        an.pauseAnimation(2);
    else if (qtd >=10)
        an.pauseAnimation(1);
    else
        an.pauseAnimation(0);

    showCollision = false;

    flags = ENTIDADE_FLAG_FISICA | ENTIDADE_FLAG_MAP_ONLY;

    gravity_speed = g_gravidade;

}

void ItemObject::render()
{
    Entidade::render();
}
void ItemObject::update(unsigned int dt)
{
    Entidade::update(dt);
    if(isColisaoEntidade(&Player::PlayerControl, pos.x, pos.y) == true)
    { //O player encostou no objeto
        executaColisao();
    }
}

void ItemObject::addLists()
{
    addToDrawListAfter();
    addToLoopList();
}
void ItemObject::executaColisao()
{
    Player::PlayerControl.addEnergy(itemType, quantidade);

    removeFromLoopList();
    removeFromDrawList();
    delete(this);
}

bool ItemObject::isValidPosition(int newX, int newY, float goX, float goY)
{
    bool retorno = Entidade::isValidPosition(newX, newY,goX,goY);
    if(retorno == false)
        this->vel.x = this->vel.y = 0;
    return retorno;
}
