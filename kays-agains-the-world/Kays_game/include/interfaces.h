//==============================================================================
/*
    Header contendo as interfaces do engine.

    Drawable  -> algum objeto que pode desenhado na tela.
    Loopable  -> algum objeto que pode efetuar o loop.

*/
//==============================================================================

#pragma once
#include "gfx.h"

class Drawable
{
    public:
        //Render operation
        virtual void render() = 0;
        void removeFromDrawList();

        void addToDrawListBefore();
        void addToDrawListAfter();
        virtual ~Drawable();
};

class Loopable {
    public:
        //Render operation
        virtual void update(unsigned int dt) = 0;
        void removeFromLoopList();

        void addToLoopList();
        virtual ~Loopable();


};



