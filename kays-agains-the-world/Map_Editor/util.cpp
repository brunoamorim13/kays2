#include "util.h"
//==============================================================================
SDL_Surface *screen = NULL;
SDL_Event event;

unsigned int NextTick, interval;
//==============================================================================

SysFont* SysFont::instance; // Declare static
//==============================================================================

_TXT SysFont::txt;  // Declare static

//==============================================================================
//          SYSFONT CLASS FUNCTIONS
//==============================================================================
SysFont& SysFont::getInstance()
{
    if (!instance) instance = new SysFont();

    return *instance;
}

void SysFont::Init_Font(char* fontname)
{
    TTF_Init();
    txt.font10 = TTF_OpenFont(fontname,10);
    txt.font12 = TTF_OpenFont(fontname,12);
    txt.font14 = TTF_OpenFont(fontname,14);
    txt.font16 = TTF_OpenFont(fontname,16);
    TTF_SetFontStyle(txt.font10, TTF_STYLE_BOLD);
    TTF_SetFontStyle(txt.font12, TTF_STYLE_BOLD);
    TTF_SetFontStyle(txt.font14, TTF_STYLE_BOLD);
    TTF_SetFontStyle(txt.font16, TTF_STYLE_BOLD); //TTF_STYLE_NORMAL
    return;
}



void SysFont::Close_Font()
{
    TTF_CloseFont(txt.font10);
    TTF_CloseFont(txt.font12);
    TTF_CloseFont(txt.font14);
    TTF_CloseFont(txt.font16);
    TTF_Quit();
}


//==============================================================================
// Extern FUNCTIONS
//==============================================================================
void FPS_Initial(int FPS)
{
    NextTick = 0;
    interval = 1 * 1000/FPS;
    return;
}

void FPS_Fn(void)
{
    if (NextTick > SDL_GetTicks())
        SDL_Delay(NextTick-SDL_GetTicks());
    NextTick = SDL_GetTicks() + interval;
    return;

}
