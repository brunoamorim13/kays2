//==============================================================================
/*
    Classe responsavel por operações graficas da tela

Exporta 3 listas como variáveis globais.

DrawListBefore -> Lista de objetos a serem desenhados na tela.
DrawListAfter  -> Lista de objetos a serem desenhados na tela acima da lista anterior.
LoopList       -> Lista de objetos que deverão executar o loop.

DrawListAfter é utlizado só para casos especiais de entidades que PRECISAM ser desenhadas
por cima de outras entidades, como os tiros e efeitos.

*/
//==============================================================================

#pragma once
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "defines.h"
#include <SDL/SDL_gfxPrimitives.h>

class Drawable;
class Loopable;
class GameEvent;


class Graphics
{
    private:
        SDL_Surface* screen;

        static Graphics *instance; // Singleton Instance

        Graphics();

    public:
        static Graphics& getInstance();
    public:
        double distance( int x1, int y1, int x2, int y2 );

    public:
        //Aplica uma surface em outra
        int apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
        int apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, int xc, int yc, int wc, int hc);
        //Aplica uma superfície a tela
        int render(int x, int y, SDL_Surface* source, int xc, int yc, int wc, int hc);
        int render(int x, int y, SDL_Surface* source, SDL_Rect* clip = NULL);

        int renderFillRect(SDL_Rect square, int r, int g, int b, int a = 255);
        int renderFillRect(int ix, int iy, int iw, int ih, int r, int g, int b, int a = 255);
        //Carrega imagem
        SDL_Surface* load_image( const char* filename );
        SDL_Surface* getScreen();

        int inicializaSDL();
        void fechaSDL();

};

//Variaveis externas
extern std::vector<Drawable*>    DrawListBefore;
extern std::vector<Drawable*>    DrawListAfter;
extern std::vector<Loopable*>    LoopList;
extern std::vector<GameEvent*>    EventList;
extern float                     g_gravidade;
extern float                     g_velMax_y;





