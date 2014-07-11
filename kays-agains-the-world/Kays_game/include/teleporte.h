#pragma once

#include "gameObject.h"
#include "interfaces.h"
#include "sdlbase.h"
#include <string>

#include "map.h"
class Teleporte : public GameObject {
    private:
        std::string nome_map;
        Vetor destPos;
        bool showCol;
        bool sameMap;
        int  timesUse;
    public:
        static std::vector<Teleporte*> TeleporteList;
        Teleporte(std::string filename, int x, int y, int w, int h, int desX, int desY);
        Teleporte(int x, int y, int w, int h, int desX, int desY, int times = -1);

        void addLists();
        void destroy();

        void render();
        void update(GameObject* dt);

};
