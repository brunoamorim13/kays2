#include "button.h"


Button::Button()
{
    posX = posY = frames = 0;
    ativo = false;
    click = false;
    surf_btn = new Sprite();
}
Button::~Button()
{
    if(surf_btn)
        delete surf_btn;
}

//Desenha na tela
void Button::render()
{
    switch(status)
    {
        case BUTTON_STATE_OUTSIDE:
            clip.x = 0;
            break;
        case BUTTON_STATE_OVER:
            clip.x = clip.w;
            break;
        case BUTTON_STATE_PRESSED:
            clip.x = clip.w*2;
            break;
    }

    surf_btn->render(posX, posY, &clip);

}

//Executa loop
void Button::handleEvents()
{
    click = false;

    if ( InputManager::getInstance()->mousePosX() > posX &&
        InputManager::getInstance()->mousePosY() > posY
        && InputManager::getInstance()->mousePosX() < posX + clip.w
        && InputManager::getInstance()->mousePosY() < posY + clip.h)
    {/// Dentro do botão

            /// Segurado
            if(InputManager::getInstance()->isMousePressed(SDL_BUTTON_LEFT) ) // Se botão esquerdo pressionado
            {
                if (frames > 2)
                    status = BUTTON_STATE_PRESSED;
            }
            else
            {
                if (frames > 1)
                    status = BUTTON_STATE_OVER;
                else
                    status =  BUTTON_STATE_OUTSIDE;
            }
            /// Clicked
            if (InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT) )
            {
                if (ativo)
                {
                    (*ClickAction)();
                } else
                {
                    click = true;
                }

            }

    }
    else
    {
        status = BUTTON_STATE_OUTSIDE;
    }

}

//Carrega imagem do botão, e numero de estados
void Button::load_image(const char* filename, int num_estados)
{
    if ( num_estados < 1 || num_estados > 3)
    {
        //Error
        return;
    }

    surf_btn = new Sprite();

    frames = num_estados;

    surf_btn->load(filename);

    //se carregou imagem
    if ( surf_btn != NULL)
    {
        clip.w = surf_btn->getWidth()/frames;
        clip.h = surf_btn->getHeight();
        clip.y = 0;
        clip.x = 0;
    }
    else
    {
        printf("Erro ao carregar imagem: %s", filename);
    }
}

//-1 mantem posição
void Button::setXY(int x, int y)
{
    if ( x >= 0 )
    {
        this->posX = x;
    }

    if ( y >= 0 )
    {
        this->posY = y;
    }
}

bool Button::isClick()
{
    if(ativo)
        return false;

    return click;
}

