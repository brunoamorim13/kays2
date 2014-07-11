#include "sprite.h"

Sprite::Sprite()
{
    surf = NULL;
}
Sprite::Sprite(const char* arquivo)
{
    surf = NULL;
    load(arquivo);
}

Sprite::~Sprite()
{
    SDL_FreeSurface(surf);
}

bool Sprite::load(const char* arquivo)
{
    unload();
    surf = SDLBase::loadImage(arquivo);

    if (surf == NULL)
    {
        printf("Arquivo nao encontrado: %s", arquivo);
        return false;
    }

    return true;
}

int Sprite::getWidth()
{
    return surf->w;
}
int Sprite::getHeight()
{
    return surf->h;
}
void Sprite::render(int x, int y, SDL_Rect* clipRect)
{
    SDLBase::gfx.render(x, y, surf, clipRect);
}

void Sprite::render(int x, int y, int cx, int cy, int cw, int ch)
{
    SDL_Rect clip = {(Sint16)cx, (Sint16)cy, (Uint16)cw, (Uint16)ch};
    render(x,y,&clip);
}

bool Sprite::isSprite()
{
    return (surf != NULL);
}

void Sprite::unload()
{
    if(surf!= NULL)
        SDL_FreeSurface(surf);
}
SDL_Surface* Sprite::getSurface()
{
    return surf;
}
void Sprite::setSurface(SDL_Surface* img)
{
    if(surf == NULL)
        surf = img;
}
//========================================================
//Sprite Layer
SpriteLayer::SpriteLayer()
{
    surf = NULL;
}
//Chama descontrutor de ~Sprite
SpriteLayer::~SpriteLayer(){
}
void SpriteLayer::deleteLayer()
{
    if(surf != NULL)
        SDL_FreeSurface(surf);
}

void SpriteLayer::createLayer(int sizeX, int sizeY)
{
    deleteLayer();

    surf = SDL_CreateRGBSurface(SDLBase::getScreen()->flags, sizeX, sizeY, SCREEN_BPP,0,0,0,0);
    SDL_FillRect( surf, &surf->clip_rect, SDL_MapRGB( SDLBase::getScreen()->format, COLOR_KEY) ); // //Pinta o layer com a colorkey
    Uint32 colorkey =   SDL_MapRGB( surf->format, COLOR_KEY );
    SDL_SetColorKey( surf, SDL_SRCCOLORKEY, colorkey );
    SDL_DisplayFormatAlpha(surf);

}
int SpriteLayer::applySprite(Sprite* source, int x, int y, int cutX, int cutY, int cutW, int cutH)
{
   return SDLBase::gfx.apply_surface(x,y, source->getSurface(), surf, cutX, cutY, cutW, cutH);
}

int SpriteLayer::applySprite(Sprite* source, int x, int y, SDL_Rect* clip)
{
    return SDLBase::gfx.apply_surface(x,y, source->getSurface(), surf, clip);
}

int SpriteLayer::applySurface(SDL_Surface* source, int x, int y, int cutX, int cutY, int cutW, int cutH)
{
   return SDLBase::gfx.apply_surface(x,y, source, surf, cutX, cutY, cutW, cutH);
}

int SpriteLayer::applySurface(SDL_Surface* source, int x, int y, SDL_Rect* clip)
{
    return SDLBase::gfx.apply_surface(x,y, source, surf, clip);
}

int SpriteLayer::render(int x,int y, SDL_Rect* clip)
{
   return SDLBase::gfx.apply_surface(x,y, surf,  SDLBase::getScreen(), clip);
}

