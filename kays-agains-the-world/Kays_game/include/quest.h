#pragma once

#include "sdlbase.h"
#include <string>
#include <sstream>

//--------- Existem dois tipos de quests, de pegar/matat/fazer X alguma coisa. Ou um objetivo unico.
//--- As com objetivos unicos serão setadas manualmente pelo setComplete enquanto as outras se completarão sozinhas ao concluir a condição.
class Quest
{
    private:
        int qtdMax;
        int qtd;
        bool collect;
        bool active;
        bool complete;
        std::string resumo;
    public:
        static std::vector<Quest*> QuestList;

        Quest(std::string resumoStr, int qtdMax);
        Quest(std::string resumoStr);

        void addQtd(int quantidade);
        void setComplete(bool completed);
        void setActive(bool ativa);
        bool isCompleted();
        bool isActive();
        int  getQtd();
        int render(int posY);

        void addLists();
        void removeLists();
};
