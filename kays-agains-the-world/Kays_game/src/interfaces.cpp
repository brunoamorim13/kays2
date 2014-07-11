#include "interfaces.h"


void Drawable::addToDrawListBefore()
{
    for(unsigned int i = 0; i < DrawListBefore.size();i++)
    {
        if (DrawListBefore[i] == this)
        {
            return; //Já existe.
        }
    }
    for(unsigned int i = 0; i < DrawListAfter.size();i++)
    {
        if (DrawListAfter[i] == this)
        {
            return; //Já existe.
        }
    }

    DrawListBefore.push_back(this);

}

void Drawable::addToDrawListAfter()
{
    for(unsigned int i = 0; i < DrawListBefore.size();i++)
    {
        if (DrawListBefore[i] == this)
        {
            return; //Já existe.
        }
    }
    for(unsigned int i = 0; i < DrawListAfter.size();i++)
    {
        if (DrawListAfter[i] == this)
        {
            return; //Já existe.
        }
    }

    DrawListAfter.push_back(this);
}

void Drawable::removeFromDrawList()
{
    for(unsigned int i = 0; i < DrawListBefore.size();i++)
    {
        if (DrawListBefore[i] == this)
        {
            DrawListBefore.erase(DrawListBefore.begin()+ i);
            return;
        }
    }
    for(unsigned int i = 0; i < DrawListAfter.size();i++)
    {
        if (DrawListAfter[i] == this)
        {
            DrawListAfter.erase(DrawListAfter.begin()+ i);
            return;
        }
    }
}
Drawable::~Drawable(){
    removeFromDrawList();
}

//======================
//Loopable
void Loopable::removeFromLoopList()
{
    for(unsigned int i = 0; i < LoopList.size();i++)
    {
        if (LoopList[i] == this)
        {
            LoopList.erase(LoopList.begin()+ i);
            break;
        }
    }
}

void Loopable::addToLoopList()
{
    for(unsigned int i = 0; i < LoopList.size();i++)
    {
        if (LoopList[i] == this)
        {
            return; //Já existe.
        }
    }

    LoopList.push_back(this);
}
Loopable::~Loopable(){
    removeFromLoopList();
}
