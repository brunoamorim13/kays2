#include "save.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "player.h"

void Save::saveGame(){
    std::ofstream save;
    save.open("savedata.save");

    Player* p = &Player::PlayerControl;


    save << p->getHP() << " " << p->getHPMax() << " " << p->getFogo() << " " << p->getFogoMax();
    save << " " << p->getAgua() << " " << p->getAguaMax() << " " << p->getAr() << " " << p->getArMax() << " " << p->getTerra() << " " << p->getTerraMax();

    for(unsigned int i = 0; i < Quest::QuestList.size(); i++){
        save <<"\n"<< i << " " << Quest::QuestList[i]->isActive() << " " <<  Quest::QuestList[i]->isCompleted() << " " << Quest::QuestList[i]->getQtd();
    }

    save.close();
}
void Save::loadGame(){

    std::ifstream myfile;
    myfile.open ("savedata.save");

    int hp, hpmax, fogo, fogomax, ar, armax, agua, aguamax, terra, terramax;

    myfile >> hp >> hpmax >> fogo >> fogomax >> agua >> aguamax >> ar >> armax >>  terra >> terramax;

    Player* p = &Player::PlayerControl;

    p->setHP(hp); p->setHPMax(hpmax); p->setFogo(fogo); p->setFogoMax(fogomax);
    p->setAgua(agua); p->setAguaMax(aguamax);p->setAr(ar);
    p->setArMax(armax); p->setTerra(terra); p->setTerraMax(terramax);

    for(unsigned int i = 0; i < Quest::QuestList.size(); i++){
        int id = -1, qtd=0;
        bool ativa=false, completa=false;
        myfile >> id >> ativa >> completa >> qtd;
        Quest::QuestList[id]->setActive(ativa);
        Quest::QuestList[id]->setComplete(completa);
        Quest::QuestList[id]->addQtd(qtd);
    }

    myfile.close();
}
