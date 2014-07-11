#include "vetor.h"


Vetor::Vetor() {x=0;y=0;}

// Produtos
// dot = escalar
inline float Vetor::dot(const Vetor b) const
{
    return x*b.x + y*b.y;
}

// cross = vetorial
inline float Vetor::cross( const Vetor b) const
{
    return x*b.y - y*b.x;
}

// Projeção desse vetor em B
//Proj = (U.V) . vetor V
//        |V|²
Vetor Vetor::project(const Vetor b)
{
    Vetor proj;
    float dp = dot(b);
    proj.x = (dp/b.dot(b)) * b.x;
    proj.y = (dp/b.dot(b)) * b.y;

    return proj;
}
//Tamanho do Vetor
float Vetor::lenght(void) const
{
    return (float) sqrt(x*x + y*y);
}
