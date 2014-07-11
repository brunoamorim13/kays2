#include "interfaceMenu.h"

InterfaceMenu InterfaceMenu::InterfaceControl;

InterfaceMenu::InterfaceMenu(){
    spriteSheet = NULL;
    spriteFogo = NULL;
    spriteGelo = NULL;
}

void InterfaceMenu::render()
{
    renderBar();
    renderEnergy();
    renderQuest();
}

void InterfaceMenu::renderBar()
{
    int hpmax = Player::PlayerControl.getHPMax();
    int hp =    Player::PlayerControl.getHP();

    int posX = (int)TILE_SIZE/4;
    int posY = (int)TILE_SIZE/2;

    //Se não tiver carregado um spritesheet, prototipo de quadrados
    if(spriteSheet == NULL)
    {
        SDL_Rect hpFull;
        SDL_Rect hpReal;

        hpFull.x = hpReal.x = posX;
        hpFull.y = hpReal.y = posY;
        hpFull.h = hpReal.h = (int)(TILE_SIZE/10);
        hpFull.w = hpReal.w = TILE_SIZE*3;

        SDL_FillRect( SDLBase::getScreen(), &hpFull, SDL_MapRGB( SDLBase::getScreen()->format, 255, 10, 10) );
        SDL_FillRect( SDLBase::getScreen(), &hpReal, SDL_MapRGB( SDLBase::getScreen()->format, 40, 255, 10) );
    }
    else
    {
        SDL_Rect clip;
        clip.x = 0; clip.y = 0;
        clip.w = 24; clip.h = 22;
        for(int i = 0; i < hpmax; i++)
        {
            if(i < hp)
            {
                clip.x = 0;
                spriteSheet->render(posX+ i*TILE_SIZE/2, posY, &clip);
            }
            else
            {
                clip.x = clip.w;
                spriteSheet->render(posX + i*TILE_SIZE/2, posY, &clip);
            }
        }
    }
}
void InterfaceMenu::renderEnergy()
{


    int posX = (int)TILE_SIZE/3;
    int posY = (int)TILE_SIZE/2;


    SDL_Rect clip;

    if(Player::PlayerControl.tiroGelo.getTime()>1500 && Player::PlayerControl.getAgua()!=0){
        clip.x =0; clip.y=0; clip.h = 32; clip.w = 32;
        spriteGelo->render(posX+5, posY+35, &clip);

    }else if(Player::PlayerControl.getAgua()!=0){

            clip.x =32; clip.y=0; clip.h = 32; clip.w = 32;
            spriteGelo->render(posX+5, posY+35, &clip);


    }


    if(Player::PlayerControl.tiroFogo.getTime()>3000 && Player::PlayerControl.getFogo()!=0){
        clip.x =0; clip.y=0; clip.h = 32; clip.w = 32;
        spriteFogo->render(posX+50, posY+30, &clip);

    }else if(Player::PlayerControl.getFogo()!=0){
        clip.x =32; clip.y=0; clip.h = 32; clip.w = 32;
        spriteFogo->render(posX+50, posY+30, &clip);
    }

}

void InterfaceMenu::renderQuest()
{
    int n = 0;
    int completa = 0;
    int n_quests = 0;
    for(unsigned int i = 0; i < Quest::QuestList.size();i++){
        if(Quest::QuestList[i]->isActive()){
            n+=Quest::QuestList[i]->render(10+10*n);
        }
        if(Quest::QuestList[i]->isCompleted())
            completa ++;
        n_quests++;
    }
    if(n>0){
        SDLBase::txt.applyText(530, 10-10, 12, 150,0,150,
                               200,200,200,"Quests:");}
}
