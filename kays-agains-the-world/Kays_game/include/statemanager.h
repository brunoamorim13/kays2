//==============================================================================
/*
    Classe timer.
*/
//==============================================================================
#pragma once
#include "inputmanager.h"
#include "sdlbase.h"

#include "menuState.h"
#include "gameState.h"
#include "presentationState.h"
#include "winloseState.h"
#include "introState.h"

#include "timer.h"

class StateManager
{
    private:
        State* estadoAtual;
        int stack;
    public:
        StateManager();
        virtual ~StateManager();

        int run();
};

// TODO (Gust#4#): Adicionar para o inimigo perseguir o player... caso entre na area de detecção dele?

// TODO (Gust#1#): Criar uma AI para os Inimigos.  E métodos de auxilio.

// TODO (Gust#1#): Adicionar para pegar e completar quests quando falar com NPCs

