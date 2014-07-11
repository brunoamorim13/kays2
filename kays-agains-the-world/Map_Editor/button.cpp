#include "button.h"


Button::Button()
{
    surf_btn = NULL;
    clip.x = 0;
    clip.y = 0;
    clip.w = 0;
    clip.h = 0;
}

Button::~Button()
{
    if ( surf_btn != NULL)
        SDL_FreeSurface(surf_btn);
}

void Button::handleEvents()
{
    if (event.button.x > posX && event.button.y > posY
        && event.button.x < posX + surf_btn->w
        && event.button.y < posY + surf_btn->h/frames)
    {/// Inside button

            /// Holded
            if(SDL_GetMouseState(NULL, NULL)& SDL_BUTTON( SDL_BUTTON_LEFT )) // If left button is pressed
            {
                if (frames > 1);
                    state = STATE_PRESSED;
            }
            else
            {
                if (frames > 2)
                    state = STATE_OVER;
                else
                    state = STATE_OUTSIDE;
            }
            /// Pressed
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                (*ClickAction)();
            }

    }
    else
    {
        state = STATE_OUTSIDE;
    }



    Render();
}

void Button::Render()
{

    switch(state)
    {
        case STATE_OUTSIDE:
            clip.y = 0;
            break;
        case STATE_PRESSED:
            clip.y = clip.h;
            break;
        case STATE_OVER:
            clip.y = clip.h * 2;
            break;
    }
    Util::apply_surface(posX,posY,surf_btn, screen, &clip);
}
bool Button::Load(char* filename, int frames)
{
    surf_btn = Util::load_image(filename);

    if (surf_btn == NULL)
        return false;

    this->frames = frames;
    clip.h = surf_btn->h/frames;
    clip.w = surf_btn->w;
    return true;
}
