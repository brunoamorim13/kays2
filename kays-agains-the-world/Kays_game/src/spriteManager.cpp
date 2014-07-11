#include "spriteManager.h"

SpriteManager SpriteManager::SpriteControl;

SpriteManager::SpriteManager()
{
    for(int i = 0; i < N_SPRITES; i++)
        vetorSprite[i] = NULL;
}

Sprite* SpriteManager::getSprite(int index)
{
    if(vetorSprite[index] == NULL){
        printf("Sprite nao carregado\n");
    }
    return vetorSprite[index];
}
void SpriteManager::loadSprite(const char* filename, int index)
{
    if(vetorSprite[index] == NULL){
        vetorSprite[index] = new Sprite(filename);
    }
}

void SpriteManager::deleteSprite(int index)
{
    if(vetorSprite[index] != NULL){
        delete vetorSprite[index];
        vetorSprite[index] = NULL;
        }
}
void SpriteManager::deleteAllSprites(){
    for(int i = 0; i < N_SPRITES;i++){
        deleteSprite(i);
    }
}
