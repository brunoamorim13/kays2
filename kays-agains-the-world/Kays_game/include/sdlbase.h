#pragma once
/*=================================================================================/
A classe SDLBase é uma coleção de atributos estáticos que serão utilizados através do sistema.

Como funções gráficas e sonoras.

/=================================================================================*/
#include "defines.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "gfx.h"
#include "text.h"
#include "sound.h"

class TextFont;
class Graphics;

class SDLBase
{
    public:
        static int inicializaSDL();
        static void fechaSDL();

        static SDL_Surface* getScreen();
        static SDL_Surface* loadImage(const char* arquivo);

        static void atualizarTela();
        static void limpaTela();

        static Graphics& gfx;
        static TextFont& txt;
        static Sound&    sfx;
};
