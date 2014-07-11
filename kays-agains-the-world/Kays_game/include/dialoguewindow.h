#pragma once



#include "sdlbase.h"
#include "vetor.h"
#include "interfaces.h"
#include <string>
#include "timer.h"


class DialogueWindow : public Drawable, public Loopable{
    public:

        DialogueWindow();

        void render();
        void update(unsigned int dt);

        void addPage();
        void addText(const char*pStr, ...);
        int nextPage();
        int nextText();
        void resetPage();
        void addLists();
        void removeLists();
        bool isVisible();

        void setVisible(bool activate);
        void setPos(Vetor posicao);
        void setPos(float x, float y);
    private:
        bool isReady;

        class DialogueEvent {
            public:
                std::string msgEvent;
                bool isWaitKey;
                bool isBreakLine;
                bool isEventCall;
                int imgID;
                int txtDelay;
        };

    private:
        std::vector<std::vector<DialogueEvent > > msgList;
        int index;
        int txtIndex;
        bool visible;
        Vetor pos;

        unsigned int delayText;
        int nChar;
        bool ended;

        int nMsgPerPage;
        bool transition;
        float offsetY;

        Timer timerText;
};
