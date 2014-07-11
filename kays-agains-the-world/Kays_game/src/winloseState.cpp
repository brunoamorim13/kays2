#include "winloseState.h"

void WinLoseState::load(int stack)
{

    m_stack = stack;

    if(stack == -1) //DERROTA
        background = new Sprite((char*)"data/img/gameOver.png");
    else //VITORIA
        background = new Sprite((char*)"data/img/creditos.png");

    if(stack == -1)    {
        //texto = "DERROTA!! VOCE DROPOU NO CHÃO!!";
        texto = " ";
        r = g = b = 255;
        offX = -170;


        b_yes = new Button();
        b_yes->load_image((char*)"data/btn/ContinueYes.png", 2);
        b_yes->setXY(279, 400);

        b_no = new Button();
        b_no->load_image((char*)"data/btn/ContinueNo.png", 2);
        b_no->setXY(279, 500);


    }
    else{
        texto = "  ";
        r = g = b = 0;
        offX = -150;
    }

    if(stack == -1) {
        SDLBase::sfx.playMusic(PLAY_DERROTA);
    }else {
        SDLBase::sfx.playMusic(PLAY_VITORIA);
    }
}

int WinLoseState::unload()
{
    delete (background);

    if(m_stack == -1){
        delete b_yes;
    }

    return m_stack;
}

eStateType WinLoseState::update(unsigned int dt)
{

    if(m_stack== -1){

        b_yes->handleEvents();

        if(b_yes->isClick()){
            m_stack=3;
            SDLBase::sfx.playSfx(PLAY_SFX_MENU);
            return GST_GAME;
        }

        b_no->handleEvents();

        if(b_no->isClick()){
            SDLBase::sfx.playSfx(PLAY_SFX_MENU);
            return GST_MENU;
        }

    }else{
    if(InputManager::getInstance()->isKeyDown(SDLK_RETURN))
        return GST_MENU;
    }

    if(InputManager::getInstance()->isKeyDown(SDLK_ESCAPE))
        return GST_QUIT;

    return GST_NONE;
}
void WinLoseState::render()
{
    background->render(0,0);

    SDLBase::txt.applyText((SCREEN_WIDTH/2)+offX,
                  (SCREEN_HEIGHT/2)-68, 16,
                            r,g,b, texto.c_str()
                            );

    if(m_stack == -1){
        b_yes->render();
        b_no->render();
    }
}
