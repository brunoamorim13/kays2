#include "statemanager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

void openProperties();

int main(int argc, char* args[])
{
    openProperties();
    StateManager game;

    return game.run();
}

void openProperties()
{
    std::ifstream file("init.conf");

    std::stringstream stream;
    std::string str;
    float value = 0;

    while(!file.eof() )
    {
        str.clear();
        stream.clear();
        std::getline(file, str,'=');
        file >> value;
        file.ignore();

        stream << str;

        stream >> str;

        if(str.compare("player_max_speedX") == 0 )
        {
            Player::PlayerControl.maxVel.x = value*TILE_SIZE;
        }

        else

        if(str.compare("player_max_speedY") == 0 )
        {
            Player::PlayerControl.maxVel.y = value*TILE_SIZE;
            g_velMax_y = value*TILE_SIZE;
        }

        else
        if(str.compare("player_aceleration") == 0 )
            Player::PlayerControl.walking_aceleration = value;
        else
        if(str.compare("player_gravity") == 0 ) {
            Player::PlayerControl.gravity_speed = value;
            g_gravidade = value;
        }
        else
        if(str.compare("player_jump_speed") == 0 )
            Player::PlayerControl.jump_speed = value*TILE_SIZE;
        else
        if(str.compare("player_stop_desaceleration") == 0 )
            Player::PlayerControl.stop_aceleration = value;
        else
        if(str.compare("player_jump_hold") == 0 )
            Player::PlayerControl.jump_hold = value;
    }
}

StateManager::StateManager()
{
    //Redireciona outputs de volta para o console.

    SDLBase::inicializaSDL();

    #ifdef __linux__
        freopen ("/dev/tty", "a", stdout);
        freopen ("/dev/tty", "a", stderr);
    #elif _WIN32
        freopen( "CON", "wt", stdout );
        freopen( "CON", "wt", stderr );
    #endif


    stack = 0;
    estadoAtual = NULL;

    InputManager::getInstance()->Update();

    estadoAtual = new IntroState
    ();
    estadoAtual->load(0);

}
StateManager::~StateManager()
{
    if(estadoAtual) {
        delete estadoAtual;
        estadoAtual = NULL;
    }

    SDLBase::fechaSDL();
}

int StateManager::run()
{
    int frame_count = 0;
    int frames = 60;
    Timer fps;
    Timer fps_update;
    Timer delta_timer;
    fps_update.start();

    bool quit = false;

    while(quit == false)
    {
        fps.start();
        //delta = SDL_GetTicks() - ticks;
       // ticks = SDL_GetTicks();

        SDLBase::limpaTela();

        if (estadoAtual == NULL)
            return -3;

        //Atualiza teclas
        InputManager::getInstance()->Update();

        if (InputManager::getInstance()->QuitGame())
        {
            quit = true;
        }

        //printf("delta = %d\n", delta);
        unsigned int delta = delta_timer.getTime();
        delta_timer.start();

        //Atualiza estado atual e verifica se houve mudança de estado
        switch( estadoAtual->update( delta ) )
        {
            case GST_NONE:
                //Não faz nada
                break;
            case GST_GAME:
                stack = estadoAtual->unload();
                delete estadoAtual;
                estadoAtual = new StateGame();
                estadoAtual->load(stack);
                break;
            case GST_MENU: // MENUs
                stack = estadoAtual->unload();
                delete estadoAtual;
                estadoAtual = new StateMenu();
                estadoAtual->load(stack);

                break;
            case GST_INTRO:
                stack = estadoAtual->unload();
                delete estadoAtual;
                estadoAtual = new PresentationState();
                estadoAtual->load(stack);
                break;
            case GST_WINLOSE:
                stack = estadoAtual->unload();
                delete estadoAtual;
                estadoAtual = new WinLoseState();
                estadoAtual->load(stack);
                break;
            case GST_QUIT:
                quit = true;
                break;
        }

        estadoAtual->render();

        if( ( fps.getTime() < 1000.f / FRAMES_PER_SECOND ) ) {
           SDL_Delay( ( 1000.f / FRAMES_PER_SECOND ) - fps.getTime() );
        }

        frame_count++;
        if( fps_update.getTime() > 1000 ) {
            fps_update.start();
            frames = frame_count;
            frame_count = 0;
            //printf("FPS = %d\n", frames);

        }

        SDLBase::txt.applyText(0,0, 12,0,0,0, 150,150,150, "FPS: %d", frames );

        SDLBase::atualizarTela();
    }

    estadoAtual->unload();
    delete estadoAtual;
    estadoAtual = NULL;

    return 0;

}
