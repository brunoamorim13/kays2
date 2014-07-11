/*********************************************************************

Classe Button,

Caso ativo seja true:
Possui um ponteiro de função que aponta para a ação do clique sobre o
botão.

Caso ativo seja false:
Ao apertar o botão, ativa a variável bool click até o próximo loop.

*********************************************************************/
#pragma once

#include "inputmanager.h"
#include "sprite.h"
#include "interfaces.h"

enum BTN_STATE {
    BUTTON_STATE_OUTSIDE = 0,
    BUTTON_STATE_OVER = 1,
    BUTTON_STATE_PRESSED = 2
};

class Button : public Drawable
{
    public:

        Button();
        virtual ~Button();
        //Desenha
        void render();

        //Executa loop
        void handleEvents();

        //Ação do botão
        void (*ClickAction)(void);
        //void (Drawable::*ClickActionBattle)(void);

        //Carrega imagem do botão, e numero de estados
        void load_image(const char* filename, int num_estados);

        //-1 mantem posição
        void setXY(int x, int y);

        //Retorna se foi apertado
        bool isClick();

        //se ativo falso, não executa click
        bool ativo;


    private:
        Sprite* surf_btn;
        int posX;
        int posY;
        int frames;
        BTN_STATE status;
        SDL_Rect clip;
        bool click;


};


