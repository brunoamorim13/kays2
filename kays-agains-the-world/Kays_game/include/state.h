//==============================================================================
/*
    Classe timer.
*/
//==============================================================================
#pragma once

typedef enum eStateType {
    GST_MENU,
    GST_INTRO,
    GST_GAME,
    GST_QUIT,
    GST_WINLOSE,
    GST_NONE
} StateType;

class State
{
    public:
        int m_stack;
        virtual void load(int stack = 0) = 0;
        virtual int unload() = 0;
        virtual eStateType update(unsigned int dt) = 0;
        virtual void render() = 0;
        virtual ~State(){}
};

