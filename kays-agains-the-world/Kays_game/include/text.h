
//==============================================================================
/*
    Classe responsavel por operações de texto na tela.

    Declara variáveis globais:
extern TextFont txt;           --> Utilizada para desenhar textos na tela.


*/
//==============================================================================

#ifndef _TEXTS__
#define _TEXTS__

#include "sdlbase.h"
#include <SDL/SDL_ttf.h>


typedef struct _TEXT {
        SDL_Surface *imgTemp ; // Guarda imagem para colar texto-
        SDL_Color fColor; // Guarda cor
        TTF_Font *font10 , *font12 , *font14 , *font16, *font22 ;
        char string[128]; // Texto a ser escrito. max 128
} _TXT;

class TextFont
{
    private:
        static TextFont *instance; // Singleton Instance
        SDL_Color black;


        TextFont(){}

    public:
        _TXT text;

        static TextFont& getInstance();

        void initFont(const char* fontname = (char*)"default.ttf");

        void closeFont();

        SDL_Surface* getTextureText(short fsize, short r, short g, short b, const char*pStr, ...);
        SDL_Surface* getTextureText(short fsize, short r, short g, short b, short r2, short g2, short b2, const char*pStr, ...);

        int applyText(short x, short y, short fsize, short r, short g, short b, const char*pStr, ... );
        int applyText(short x, short y, short fsize, short r, short g, short b, short r2, short g2, short b2, const char*pStr, ... );

        void applyTextAlpha(short x, short y, short fsize, short r, short g, short b, int alpha, const char*pStr, ... );
        void applyTextAlpha(short x, short y, short fsize, short r, short g, short b, short r2, short g2, short b2, int alpha, const char*pStr, ... );

        ~TextFont()
        {
        }

};


extern TextFont txt;

#endif


