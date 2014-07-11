
//==============================================================================
/*
    Classe responsavel por operações de texto na tela.

    Declara variáveis globais:
extern TextFont text;           --> Utilizada para desenhar textos na tela.


*/
//==============================================================================
#include "text.h"
//Singleton
TextFont txt = TextFont::getInstance();

TextFont* TextFont::instance;

TextFont& TextFont::getInstance()
{
    if (!instance)
    {
        instance = new TextFont();
    }

    return *instance;
}

void TextFont::initFont(const char* fontname)
{
    TTF_Init();
    text.font10 = TTF_OpenFont(fontname,10);
    text.font12 = TTF_OpenFont(fontname,12);
    text.font14 = TTF_OpenFont(fontname,14);
    text.font16 = TTF_OpenFont(fontname,16);
    text.font22 = TTF_OpenFont(fontname,22);
    black.r = 255;
    black.g = 255;
    black.b = 255;

    if (text.font10 == NULL)
    {
        //Error
        printf("Erro ao abrir fonte %s", fontname);
    }
    else
    {
        TTF_SetFontStyle(text.font10, TTF_STYLE_BOLD);
        TTF_SetFontStyle(text.font12, TTF_STYLE_BOLD);
        TTF_SetFontStyle(text.font14, TTF_STYLE_BOLD);
        TTF_SetFontStyle(text.font16, TTF_STYLE_BOLD);
        TTF_SetFontStyle(text.font22, TTF_STYLE_BOLD);
    }

    return;
}



void TextFont::closeFont()
{
    TTF_CloseFont(text.font10);
    TTF_CloseFont(text.font12);
    TTF_CloseFont(text.font14);
    TTF_CloseFont(text.font16);
    TTF_CloseFont(text.font22);
    TTF_Quit();
}


SDL_Surface* TextFont::getTextureText(short fsize, short r, short g, short b, const char*pStr, ...)
{
    va_list valist; // Hold information about variables
    va_start(valist, pStr); // Initialize the variable argument list
    vsprintf(text.string, pStr, valist); // Print formated variable arg. list to string
    va_end(valist); // Needs to be executed before the function can return any value

    text.fColor.r = r;
    text.fColor.g = g;
    text.fColor.b = b;
    black.r = 255;
    black.g = 255;
    black.b = 255;
    //Set Outline
    TTF_SetFontOutline(text.font10, 2);
    TTF_SetFontOutline(text.font12, 2);
    TTF_SetFontOutline(text.font14, 2);
    TTF_SetFontOutline(text.font16, 2);
    TTF_SetFontOutline(text.font22, 2);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, black); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, black); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, black); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, black); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, black); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", black); break;
    }  // End switch
    SDL_Surface* blitSurf;
    TTF_SetFontOutline(text.font10, 0);
    TTF_SetFontOutline(text.font12, 0);
    TTF_SetFontOutline(text.font14, 0);
    TTF_SetFontOutline(text.font16, 0);
    TTF_SetFontOutline(text.font22, 0);
    switch(fsize)
    {
        case 10: blitSurf = TTF_RenderUTF8_Blended(text.font10, text.string, text.fColor); break;
        case 12: blitSurf = TTF_RenderUTF8_Blended(text.font12, text.string, text.fColor); break;
        case 14: blitSurf = TTF_RenderUTF8_Blended(text.font14, text.string, text.fColor); break;
        case 16: blitSurf = TTF_RenderUTF8_Blended(text.font16, text.string, text.fColor); break;
        case 22: blitSurf = TTF_RenderUTF8_Blended(text.font22, text.string, text.fColor); break;
        default: blitSurf = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", text.fColor); break;
    }  // End switch
    SDL_Rect dest = { 2, 2, 0, 0};
    SDL_BlitSurface(blitSurf,NULL,text.imgTemp,&dest);
    SDL_FreeSurface(blitSurf);
    return text.imgTemp;
}


int TextFont::applyText(short x, short y, short fsize, short r, short g, short b, const char*pStr, ... )
{
    va_list valist; // Hold information about variables
    va_start(valist, pStr); // Initialize the variable argument list
    vsprintf(text.string, pStr, valist); // Print formated variable arg. list to string
    va_end(valist); // Needs to be executed before the function can return any value

    text.fColor.r = r;
    text.fColor.g = g;
    text.fColor.b = b;
    black.b = 255;
    black.g = 255;
    black.r = 255;

    //Set Outline
    TTF_SetFontOutline(text.font10, 1);
    TTF_SetFontOutline(text.font12, 1);
    TTF_SetFontOutline(text.font14, 1);
    TTF_SetFontOutline(text.font16, 1);
    TTF_SetFontOutline(text.font22, 1);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, black); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, black); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, black); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, black); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, black); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", black); break;
    }  // End switch
    SDLBase::gfx.render(x-1,y-1, text.imgTemp, NULL);
    SDL_FreeSurface(text.imgTemp);
    //Retira Outline
    TTF_SetFontOutline(text.font10, 0);
    TTF_SetFontOutline(text.font12, 0);
    TTF_SetFontOutline(text.font14, 0);
    TTF_SetFontOutline(text.font16, 0);
    TTF_SetFontOutline(text.font22, 0);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, text.fColor); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, text.fColor); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, text.fColor); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, text.fColor); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, text.fColor); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", text.fColor); break;
    }  // End switch
    SDLBase::gfx.render(x,y, text.imgTemp, NULL);

    int sizeX = text.imgTemp->w;
    SDL_FreeSurface(text.imgTemp);
    return sizeX;
}

void TextFont::applyTextAlpha(short x, short y, short fsize, short r, short g, short b, int alpha, const char*pStr, ... )
{
    va_list valist; // Informações das variaveis
    va_start(valist, pStr); // Inicia a lista de argumentos das variaveis
    vsprintf(text.string, pStr, valist); // Escreve os argumentos das variaveis formatados para um string
    va_end(valist); // Precisa ser executado para finalizar o processo

    if (alpha > 255)
        alpha = 255;
    else if (alpha < 0)
        alpha = 0;

    text.fColor.r = r;
    text.fColor.g = g;
    text.fColor.b = b;

    black.r = 255;
    black.g = 255;
    black.b = 255;
    //Set Outline
    TTF_SetFontOutline(text.font10, 1);
    TTF_SetFontOutline(text.font12, 1);
    TTF_SetFontOutline(text.font14, 1);
    TTF_SetFontOutline(text.font16, 1);
    TTF_SetFontOutline(text.font22, 1);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, black); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, black); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, black); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, black); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, black); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", black); break;
    }  // End switch

    SDL_SetAlpha(text.imgTemp, SDL_SRCALPHA|SDL_RLEACCEL, 255-alpha); // Sets Alpha
    SDLBase::gfx.render(x-1,y-1, text.imgTemp, NULL);

    SDL_FreeSurface(text.imgTemp);

    //Retira Outline
    TTF_SetFontOutline(text.font10, 0);
    TTF_SetFontOutline(text.font12, 0);
    TTF_SetFontOutline(text.font14, 0);
    TTF_SetFontOutline(text.font16, 0);
    TTF_SetFontOutline(text.font22, 0);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, text.fColor); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, text.fColor); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, text.fColor); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, text.fColor); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, text.fColor); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", text.fColor); break;
    }  // End switch

    SDL_SetAlpha(text.imgTemp, SDL_SRCALPHA|SDL_RLEACCEL, 255-alpha); // Sets Alpha
    SDLBase::gfx.render(x,y, text.imgTemp, NULL);
    SDL_FreeSurface(text.imgTemp);
    return;
}

void TextFont::applyTextAlpha(short x, short y, short fsize, short r, short g, short b, short r2, short g2, short b2, int alpha, const char*pStr, ... ) {
    va_list valist; // Informações das variaveis
    va_start(valist, pStr); // Inicia a lista de argumentos das variaveis
    vsprintf(text.string, pStr, valist); // Escreve os argumentos das variaveis formatados para um string
    va_end(valist); // Precisa ser executado para finalizar o processo

    if (alpha > 255)
        alpha = 255;
    else if (alpha < 0)
        alpha = 0;

    text.fColor.r = r;
    text.fColor.g = g;
    text.fColor.b = b;
    black.r = r2;
    black.g = g2;
    black.b = b2;
    //Set Outline
    TTF_SetFontOutline(text.font10, 1);
    TTF_SetFontOutline(text.font12, 1);
    TTF_SetFontOutline(text.font14, 1);
    TTF_SetFontOutline(text.font16, 1);
    TTF_SetFontOutline(text.font22, 1);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, black); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, black); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, black); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, black); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, black); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", black); break;
    }  // End switch

    SDL_SetAlpha(text.imgTemp, SDL_SRCALPHA|SDL_RLEACCEL, 255-alpha); // Sets Alpha
    SDLBase::gfx.render(x-1,y-1, text.imgTemp, NULL);

    SDL_FreeSurface(text.imgTemp);

    //Retira Outline
    TTF_SetFontOutline(text.font10, 0);
    TTF_SetFontOutline(text.font12, 0);
    TTF_SetFontOutline(text.font14, 0);
    TTF_SetFontOutline(text.font16, 0);
    TTF_SetFontOutline(text.font22, 0);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, text.fColor); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, text.fColor); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, text.fColor); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, text.fColor); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, text.fColor); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", text.fColor); break;
    }  // End switch

    SDL_SetAlpha(text.imgTemp, SDL_SRCALPHA|SDL_RLEACCEL, 255-alpha); // Sets Alpha
    SDLBase::gfx.render(x,y, text.imgTemp, NULL);
    SDL_FreeSurface(text.imgTemp);
    return;
}

int TextFont::applyText(short x, short y, short fsize, short r, short g, short b, short r2, short g2, short b2, const char*pStr, ... ) {
    va_list valist; // Hold information about variables
    va_start(valist, pStr); // Initialize the variable argument list
    vsprintf(text.string, pStr, valist); // Print formated variable arg. list to string
    va_end(valist); // Needs to be executed before the function can return any value

    text.fColor.r = r;
    text.fColor.g = g;
    text.fColor.b = b;
    black.r = r2;
    black.g = g2;
    black.b = b2;

    //Set Outline
    TTF_SetFontOutline(text.font10, 1);
    TTF_SetFontOutline(text.font12, 1);
    TTF_SetFontOutline(text.font14, 1);
    TTF_SetFontOutline(text.font16, 1);
    TTF_SetFontOutline(text.font22, 1);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, black); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, black); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, black); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, black); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, black); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", black); break;
    }  // End switch
    SDLBase::gfx.render(x-1,y-1, text.imgTemp, NULL);
    SDL_FreeSurface(text.imgTemp);
    //Retira Outline
    TTF_SetFontOutline(text.font10, 0);
    TTF_SetFontOutline(text.font12, 0);
    TTF_SetFontOutline(text.font14, 0);
    TTF_SetFontOutline(text.font16, 0);
    TTF_SetFontOutline(text.font22, 0);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, text.fColor); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, text.fColor); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, text.fColor); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, text.fColor); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, text.fColor); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", text.fColor); break;
    }  // End switch
    SDLBase::gfx.render(x,y, text.imgTemp, NULL);

    int sizeX = text.imgTemp->w;
    SDL_FreeSurface(text.imgTemp);
    return sizeX;
}

SDL_Surface* TextFont::getTextureText(short fsize, short r, short g, short b, short r2, short g2, short b2, const char*pStr, ...)
{
    va_list valist; // Hold information about variables
    va_start(valist, pStr); // Initialize the variable argument list
    vsprintf(text.string, pStr, valist); // Print formated variable arg. list to string
    va_end(valist); // Needs to be executed before the function can return any value

    text.fColor.r = r;
    text.fColor.g = g;
    text.fColor.b = b;
    black.r = r2;
    black.g = g2;
    black.b = b2;
    //Set Outline
    TTF_SetFontOutline(text.font10, 2);
    TTF_SetFontOutline(text.font12, 2);
    TTF_SetFontOutline(text.font14, 2);
    TTF_SetFontOutline(text.font16, 2);
    TTF_SetFontOutline(text.font22, 2);
    switch(fsize)
    {
        case 10: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, text.string, black); break;
        case 12: text.imgTemp = TTF_RenderUTF8_Blended(text.font12, text.string, black); break;
        case 14: text.imgTemp = TTF_RenderUTF8_Blended(text.font14, text.string, black); break;
        case 16: text.imgTemp = TTF_RenderUTF8_Blended(text.font16, text.string, black); break;
        case 22: text.imgTemp = TTF_RenderUTF8_Blended(text.font22, text.string, black); break;
        default: text.imgTemp = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", black); break;
    }  // End switch
    SDL_Surface* blitSurf;
    TTF_SetFontOutline(text.font10, 0);
    TTF_SetFontOutline(text.font12, 0);
    TTF_SetFontOutline(text.font14, 0);
    TTF_SetFontOutline(text.font16, 0);
    TTF_SetFontOutline(text.font22, 0);
    switch(fsize)
    {
        case 10: blitSurf = TTF_RenderUTF8_Blended(text.font10, text.string, text.fColor); break;
        case 12: blitSurf = TTF_RenderUTF8_Blended(text.font12, text.string, text.fColor); break;
        case 14: blitSurf = TTF_RenderUTF8_Blended(text.font14, text.string, text.fColor); break;
        case 16: blitSurf = TTF_RenderUTF8_Blended(text.font16, text.string, text.fColor); break;
        case 22: blitSurf = TTF_RenderUTF8_Blended(text.font22, text.string, text.fColor); break;
        default: blitSurf = TTF_RenderUTF8_Blended(text.font10, "Font is only 10, 12, 14 or 16.", text.fColor); break;
    }  // End switch
    SDL_Rect dest = { 2, 2, 0, 0};
    SDL_BlitSurface(blitSurf,NULL,text.imgTemp,&dest);
    SDL_FreeSurface(blitSurf);
    return text.imgTemp;
}
