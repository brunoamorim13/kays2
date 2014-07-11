//==============================================================================
/*
    A classe Vetor que Coordenada que armazena uma posição float x e y

    A classe define as operações comuns de vetores como produto escalar,
    vetorial, comprimento, etc.

*/
//==============================================================================
#pragma once

#include <math.h>

//
// NOTA: perproduct = Normal do vetor
//
//           /  left hand perproduct,  x = -a.y, y = a.x;
//          /
//          ------>
//         /
//        /     left hand perproduct,  x = a.y, y = -a.x;

class Vetor
{
    public:

        float x;
        float y;

        Vetor(float fX, float fY) : x(fX), y(fY) {}
        Vetor();
        // escalar
        float dot(const Vetor b) const;
        // vetorial
        float cross( const Vetor b) const;
        // Projeção desse vetor em B
        Vetor project(const Vetor b);
        float lenght(void) const;

        //Operadores
        inline Vetor operator + (const Vetor &V)   const
        { return Vetor(x+V.x, y+V.y); }

        inline Vetor operator - (const Vetor &V)   const
        { return Vetor(x-V.x, y-V.y); }

        inline Vetor operator * (float s)           const
        { return Vetor(x*s, y*s); }

        inline Vetor operator / (float s)           const
        { return Vetor(x/s, y/s); }

};




