#pragma once

#include "entidade.h"
#include "player.h"
#include "interfaces.h"

typedef enum eItemType
{    // Adiciona com | e testa com &
    ITEM_TYPE_NADA          =-1,
    ITEM_TYPE_FOGO          = 0,
    ITEM_TYPE_TERRA         = 1,
    ITEM_TYPE_AGUA          = 2,
    ITEM_TYPE_AR            = 3,
    ITEM_TYPE_HP            = 4,
    ITEM_TYPE_EQUIP         ,
    ITEM_TYPE_RESOURCE
}ItemType;

class ItemObject : public Entidade, public Loopable, public Drawable
{
    public:
        //Contem todos os sprites dos itens caidos na tela. Carregado pelo gameState
        static Sprite* spr_itens;
    public:
        ItemObject(Vetor posicao, ItemType flagsItem, int qtd);

        void render();
        void update(unsigned int dt);

        void executaColisao();
        void addLists();

        int itemType;
        int quantidade;

        virtual bool isValidPosition(int newX, int newY, float goX, float goY);

};
