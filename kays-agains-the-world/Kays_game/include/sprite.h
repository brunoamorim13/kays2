#pragma once

//* ========================================================= */
//  Classe responsável por fazer as alocações de imagens e
//   desenhá-las na tela.
//
//* ========================================================= */
#include "sdlbase.h"
class Sprite
{
    protected:
        SDL_Surface* surf;
    public:
        Sprite();
        Sprite(const char* arquivo);
        virtual ~Sprite();

        bool load(const char* arquivo);
        void unload();

        void render(int x, int y, SDL_Rect* clip = NULL);
        void render(int x, int y, int cx, int cy, int cw, int ch);
    public:
        int getWidth();
        int getHeight();
        bool isSprite();
        SDL_Surface* getSurface();
        void setSurface(SDL_Surface* img);
};

class SpriteLayer : public Sprite
{
    public:
        SpriteLayer();
        ~SpriteLayer();
        int applySprite(Sprite* source, int x, int y, int cutX, int cutY, int cutW, int cutH);
        int applySprite(Sprite* source, int x, int y, SDL_Rect* clip);
        int applySurface(SDL_Surface* source, int x, int y, int cutX, int cutY, int cutW, int cutH);
        int applySurface(SDL_Surface* source, int x, int y, SDL_Rect* clip);
        void createLayer(int sizeX, int sizeY);
        void deleteLayer();
        int render(int x,int y,SDL_Rect* clip = NULL);
};
