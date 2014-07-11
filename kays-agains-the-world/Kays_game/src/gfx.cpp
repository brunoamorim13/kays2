
#include "gfx.h"
#include <math.h>

Graphics* Graphics::instance; // Singleton Instance

Graphics::Graphics(){}

Graphics& Graphics::getInstance()
{
    if (!instance)
    {
        instance = new Graphics();
    }

    return *instance;
}

//==============================================================================
// Declaração das variáveis globais externas
//==============================================================================

std::vector<Drawable*>    DrawListBefore;
std::vector<Drawable*>    DrawListAfter;
std::vector<Loopable*>    LoopList;
std::vector<GameEvent*>   EventList;
float                     g_gravidade;
float                     g_velMax_y;

//==============================================================================
// Inicializa o SDL
//==============================================================================
int Graphics::inicializaSDL()
{
    atexit(SDL_Quit);

    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0 )
        return -1;

    SDL_WM_SetCaption(NOME_JANELA, NOME_ICONE);
    SDL_WM_SetIcon(SDL_LoadBMP(NOME_ICONE), NULL);

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
                     SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (screen == NULL)
        return -2;

    //Redireciona outputs de volta para o console.
    freopen( "CON", "wt", stdout );

    return 0;
}
void Graphics::fechaSDL()
{
    SDL_Quit();
}
//==============================================================================
// Retorna a distancia entre 2 pontos
//==============================================================================
double Graphics::distance( int x1, int y1, int x2, int y2 )
{
    return sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );
}

//==============================================================================
// Aplica uma superfície SDL_Surface* em outra.
//==============================================================================
int Graphics::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    // Cria temp para deslocamentos
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //Apply the surface
    return SDL_BlitSurface( source, clip, destination, &offset );
}

//==============================================================================
// Aplica uma superfície SDL_Surface* em outra.
//==============================================================================
int Graphics::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, int xc, int yc, int wc, int hc)
{
    // Cria temp para deslocamentos
    SDL_Rect offset;
    SDL_Rect clip;

    clip.x = xc;
    clip.y = yc;
    clip.h = hc;
    clip.w = wc;

    offset.x = x;
    offset.y = y;

    // Aplica superficie
    return SDL_BlitSurface( source, &clip, destination, &offset );
}

int Graphics::render(int x, int y, SDL_Surface* source, int xc, int yc, int wc, int hc)
{
    return apply_surface(x,y, source, screen, xc, yc, wc, hc);
}
int Graphics::render(int x, int y, SDL_Surface* source, SDL_Rect* clip)
{
    return apply_surface(x,y, source, screen, clip);
}

//==============================================================================
// Carrega uma imagem e retorna como um SDL_Surface*
//==============================================================================
SDL_Surface* Graphics::load_image( const char* filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    //Carrega a imagem
    loadedImage = IMG_Load( filename );

    if( loadedImage != NULL )
    {
        if (!loadedImage->format->Amask)
            optimizedImage = SDL_DisplayFormat( loadedImage );
        else
            optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        // Libera imagem antiga
        SDL_FreeSurface( loadedImage );

        Uint32 colorkey =   SDL_MapRGB( optimizedImage->format, COLOR_KEY );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    }
    else
    {
        printf("Imagem não encontrada em: %s", filename);
    }
        // Return optimized image
    return optimizedImage;
}

//==============================================================================
// Preenche um quadrado na tela
//==============================================================================
int Graphics::renderFillRect(SDL_Rect square, int r, int g, int b, int a){
    int x1= square.x;
    int y1= square.y;
    int x2= x1+square.w;
    int y2= y1+square.h;
    return boxRGBA(screen,x1,y1,x2,y2, r,g,b,a);
}
int Graphics::renderFillRect(int ix, int iy, int iw, int ih, int r, int g, int b, int a) {
    int x2= ix+iw;
    int y2= iy+ih;
    return boxRGBA(screen,ix,iy,x2,y2, r,g,b,a);
}


SDL_Surface* Graphics::getScreen()
{
    return screen;
}



