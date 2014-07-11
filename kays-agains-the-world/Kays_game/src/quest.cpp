#include "quest.h"


std::vector<Quest*> Quest::QuestList;

Quest::Quest(std::string resumoStr, int quantidadeMax)
{
    resumo = resumoStr;
    qtdMax = quantidadeMax;
    qtd = 0;
    complete = false;
    collect = true;
    active = false;
}
Quest::Quest(std::string resumoStr)
{
    resumo = resumoStr;
    qtdMax = 0;
    qtd = 0;
    complete = false;
    collect = false;
    active = false;
}

int Quest::render(int posY)
{
    std::stringstream text;
    text << resumo;
    int red = 255, green = 255, blue = 255;
    if(complete){
        red = 0; blue = 0;
        green = 140;
        }

    if(collect == true) {
        text << " " << qtd << "/" << qtdMax;}


    //Quebra o texto final quando encontrar \n e imprime cada texto numa linha.
    std::istringstream tokenizer(text.str());
    std::string token;
    int n_linhas = 0;
    while ( getline(tokenizer, token, '\n') )
    {
        SDLBase::txt.applyText(465,posY+10*n_linhas, 12, red,green,blue, 150,150,150, token.c_str());
        n_linhas++;
    }

    return n_linhas;
}

void Quest::addQtd(int quantidade){
    if(active == false) return;
    qtd+=quantidade;
    if(qtd >= qtdMax){
        complete = true;
    }
}
void Quest::setComplete(bool completed)
{
    if(active == false) return;
    this->complete = completed;
}
void Quest::setActive(bool ativa)
{
    this->active = ativa;
}
bool Quest::isCompleted()
{
    return complete;
}
bool Quest::isActive()
{
    return active;
}

void Quest::addLists(){
    for(unsigned int i = 0; i < QuestList.size();i++)
    {
        if (QuestList[i] == this)
        {
            return; //Já existe.
        }
    }
    QuestList.push_back(this);
}
void Quest::removeLists(){
    for(unsigned int i = 0; i < QuestList.size();i++)
    {
        if (QuestList[i] == this)
        {
            QuestList.erase(QuestList.begin()+ i);
            return;
        }
    }
}

int  Quest::getQtd(){
    return qtd;
}
