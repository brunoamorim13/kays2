#pragma once

#include "personagem.h"
#include "quest.h"
#include "dialoguewindow.h"
#include "inputmanager.h"
#include "player.h"
#define QUEST_INACTIVE 0
#define QUEST_INPROGRESS 1
#define QUEST_DONE 2
#define QUEST_COMPLETE 3


class NPC : public Personagem{
    private:
        int quest;
        int questState;
        std::string nome;
        int offsetXMinus;

    public:
        NPC();
        ~NPC();

        void setQuest(int q_number);
        DialogueWindow chat;
        DialogueWindow startTxt;
        DialogueWindow progressTxt;
        DialogueWindow doneTxt;


        void update(unsigned int dt);
        void render();
        void setNome(std::string name);
        void setOffsetXMinus(int offX);//Offset da posição do nome para ficar centralizado(fake)
        virtual void executaColisao();
        virtual bool isValidPosition(int newX, int newY, float goX, float goY);
        void updateQuestState();
};

