//==============================================================================
/*
    The Util class contains all the surface related static functions

    The SysFont class contains a static struct and a static apply_font the render
    fonts but it MUST be instanciated by the Font_Init first in a instanciable
    SysFont variable



    NOTE TO SELF:
    Use SDL_WaitEvent( &event ) to skip events;

*/
//==============================================================================

#ifndef _UTILS_H_
#define _UTILS_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

extern SDL_Surface *screen;
extern SDL_Event event;


class Util {


    public:
        /// STATIC FUNCTIONS

        static inline SDL_Surface* load_image(char* filename, int alpha = 0)
        {// Load a image
            SDL_Surface* loadedImage = NULL; //Temporary storage of the image to be loaded
            SDL_Surface* optimizedImage = NULL; //The optimized image returned
            loadedImage = IMG_Load( filename ); //Load the image
            if(loadedImage==NULL)
            {
                fprintf(stderr,"Missing image %s : %s\n",filename,IMG_GetError());
                SDL_FreeSurface(loadedImage);
                return NULL;
            }
            SDL_SetColorKey(loadedImage,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(loadedImage->format,66,154,156)); //ColorKey
            if(alpha) SDL_SetAlpha(loadedImage, SDL_SRCALPHA|SDL_RLEACCEL , 255 - alpha); //Make the apha
            optimizedImage = SDL_DisplayFormat( loadedImage ); // Adjust to screen format
            SDL_FreeSurface( loadedImage ); // Free old image
            return optimizedImage; // Return optimized image
        }


        static inline void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL, int alpha = 255)
        { //Apply one surface onto another

            if(alpha != SDL_ALPHA_OPAQUE) {
                SDL_SetAlpha(source, SDL_SRCALPHA, alpha);
            }
            // Create a tempory rect to hold the offsets
            SDL_Rect offset;
            offset.x = x;
            offset.y = y;
            //Apply the surface
            SDL_BlitSurface( source, clip, destination, &offset );

            //Volta alpha ao normal
            if(alpha != SDL_ALPHA_OPAQUE) {
                SDL_SetAlpha(source, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
            }
        }

        // From Engine
        static inline void RenderBorder(short desX, short desY, short desW, short desH, short space, int bgColor = 5921370)
        {
            SDL_Rect menuBorder[5];

            /// CREATES A BORDER
            menuBorder[0].x = desX + 0;                     // Upper left -> down
            menuBorder[1].x = desX + 0;                     // Bottom left -> left
            menuBorder[2].x = desX + desW + space;          // Upper right -> down
            menuBorder[3].x = desX + 0;                     // Upper left -> left

            menuBorder[0].y = desY + 0;
            menuBorder[1].y = desY + desH + space;
            menuBorder[2].y = desY + 0;
            menuBorder[3].y = desY + 0;

            menuBorder[0].w = 1;
            menuBorder[1].w = desW + space;
            menuBorder[2].w = 1;
            menuBorder[3].w = desW + space;

            menuBorder[0].h = desH + space;
            menuBorder[1].h = 1;
            menuBorder[2].h = desH + space;
            menuBorder[3].h = 1;

            /// Background Color

            menuBorder[4].x = desX + 1;
            menuBorder[4].y = desY + 1;
            menuBorder[4].w = desW + space - 2;
            menuBorder[4].h = desH + space - 2;

            for (short i = 0; i<4; i++)
                SDL_FillRect(screen, &menuBorder[i], SDL_MapRGB(screen->format, 255,255,255));

            if (bgColor == -1)
                return;

            SDL_FillRect(screen, &menuBorder[4], bgColor);

        }


};
#endif


#ifndef _SYSFONT_H_
#define _SYSFONT_H_

typedef struct _TEXT {
        SDL_Surface *imgTemp ; // Store img of text for blit
        SDL_Rect imgRect ; // Store (x,y) of text for blit
        SDL_Color fColor;
        TTF_Font *font10 , *font12 , *font14 , *font16 ;
        char string[128]; // A string that contains 128 char
} _TXT;

class SysFont{
    private:



        static SysFont *instance; // Singleton Instance

        SysFont(){}

    public:
        static _TXT txt;

       static SysFont& getInstance();

        void Init_Font(char* fontname = "default.ttf");

        void Close_Font();

        static inline void apply_text(short x, short y, short fsize, short r, short g, short b, const char*pStr, ... )
        {
            va_list valist; // Hold information about variables
            va_start(valist, pStr); // Initialize the variable argument list
            vsprintf(SysFont::txt.string, pStr, valist); // Print formated variable arg. list to string
            va_end(valist); // Needs to be executed before the function can return any value

            txt.imgRect.x = x;
            txt.imgRect.y = y;
            txt.fColor.r = r;
            txt.fColor.g = g;
            txt.fColor.b = b;
            switch(fsize)
            {
                case 10: txt.imgTemp = TTF_RenderText_Solid(txt.font10, txt.string, txt.fColor); break;
                case 12: txt.imgTemp = TTF_RenderText_Solid(txt.font12, txt.string, txt.fColor); break;
                case 14: txt.imgTemp = TTF_RenderText_Solid(txt.font14, txt.string, txt.fColor); break;
                case 16: txt.imgTemp = TTF_RenderText_Solid(txt.font16, txt.string, txt.fColor); break;
                default: txt.imgTemp = TTF_RenderText_Solid(txt.font10, "Font is only 10, 12, 14 or 16.", txt.fColor); break;
            }  // End switch
            SDL_BlitSurface(txt.imgTemp, NULL, screen, &txt.imgRect);
            SDL_FreeSurface(txt.imgTemp);
            return;
        }

        static inline void apply_textAlpha(short x, short y, short fsize, short r, short g, short b, int alpha, const char*pStr, ... )
        {
            va_list valist; // Hold information about variables
            va_start(valist, pStr); // Initialize the variable argument list
            vsprintf(SysFont::txt.string, pStr, valist); // Print formated variable arg. list to string
            va_end(valist); // Needs to be executed before the function can return any value

            if (alpha > 255)
                alpha = 255;
            else if (alpha < 0)
                alpha = 0;

            txt.imgRect.x = x;
            txt.imgRect.y = y;
            txt.fColor.r = r;
            txt.fColor.g = g;
            txt.fColor.b = b;
            switch(fsize)
            {
                case 10: txt.imgTemp = TTF_RenderText_Solid(txt.font10, txt.string, txt.fColor); break;
                case 12: txt.imgTemp = TTF_RenderText_Solid(txt.font12, txt.string, txt.fColor); break;
                case 14: txt.imgTemp = TTF_RenderText_Solid(txt.font14, txt.string, txt.fColor); break;
                case 16: txt.imgTemp = TTF_RenderText_Solid(txt.font16, txt.string, txt.fColor); break;
                default: txt.imgTemp = TTF_RenderText_Solid(txt.font10, "Font is only 10, 12, 14 or 16.", txt.fColor); break;
            }  // End switch

            SDL_SetAlpha(txt.imgTemp, SDL_SRCALPHA|SDL_RLEACCEL, 255-alpha); // Sets Alpha
            SDL_BlitSurface(txt.imgTemp, NULL, screen, &txt.imgRect);
            SDL_FreeSurface(txt.imgTemp);
            return;
        }

};

extern void FPS_Initial(int FPS);

inline void FPS_Fn(void);
#endif
