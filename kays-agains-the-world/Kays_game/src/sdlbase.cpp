#include "sdlbase.h"


Graphics& SDLBase::gfx = Graphics::getInstance();
TextFont& SDLBase::txt = TextFont::getInstance();
Sound&    SDLBase::sfx =    Sound::getInstance();


//==============================================================================
// Inicializa o SDL
//==============================================================================
int SDLBase::inicializaSDL()
{
    int retorno = gfx.inicializaSDL();
    txt.initFont(FONT_NAME);
    sfx.init();
    sfx.loadAllSounds();
    return retorno;
}

void SDLBase::fechaSDL()
{
    txt.closeFont();
    sfx.closeSound();
    gfx.fechaSDL();
}

//==============================================================================
// Carrega uma imagem e retorna como um SDL_Surface*
//==============================================================================
SDL_Surface* SDLBase::loadImage(const char* arquivo)
{
    return gfx.load_image(arquivo);
}

//Atualiza a tela
void SDLBase::atualizarTela()
{
    SDL_Flip(gfx.getScreen());
}

void SDLBase::limpaTela()
{
    SDL_FillRect( gfx.getScreen(), &gfx.getScreen()->clip_rect, SDL_MapRGB( gfx.getScreen()->format, 255, 255, 255) );
}

SDL_Surface* SDLBase::getScreen()
{
    return gfx.getScreen();
}
