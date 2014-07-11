#include "npc.h"

#include "save.h"


NPC::NPC() : Personagem::Personagem() {
    quest = -1;
    flags = ENTIDADE_FLAG_MAP_ONLY_COLIDE | ENTIDADE_FLAG_NPC | ENTIDADE_FLAG_FISICA;
    showCollision = false;
    gravity_speed = g_gravidade;
    maxVel.y = g_velMax_y;
    chat.addLists();
    nome = "Joe(NPC)";
    offsetXMinus = 13;
    an.pauseAnimation(0);
    actionMovement = ACT_NONE;
}
NPC::~NPC(){
    chat.removeLists();
}
void NPC::setQuest(int q_number){
   // if(q_number >= (int)Quest::QuestList.size() || q_number < 0)
   //     return;

    quest = q_number;
}
void NPC::setNome(std::string name)
{
    nome = name;
}
void NPC::executaColisao()
{
    if(entidadeColidida.empty() == false)
    {
        //Só colide com o player
        if(InputManager::getInstance()->isKeyDown(SDLK_x) || InputManager::getInstance()->getButtonState(0,1)){

            Player::PlayerControl.canShot = false;
            if(chat.isVisible() == false)
                chat.setVisible(true);
            else{//Se não tiver mais páginas, tira a mensagem e ativa a quest
                if(chat.nextPage() == false){ //Se for a ultima página, verifica ação
                    if(quest == -1){
                        Player::PlayerControl.setHP(100);
                        Save::saveGame();
                        TextSplash* t = new TextSplash(pos.x, pos.y, 100,100,100, "Game Saved!");
                        t->addLists();
                        TextSplash* t2 = new TextSplash(pos.x, pos.y-12, 155,0,0, "HP Restored!");
                        t2->addLists();
                    }
                    if(quest >= 0 && quest < (int)Quest::QuestList.size()){//Se a quest existir
                         updateQuestState();
                         if(questState==QUEST_DONE){ //Quest completa, recebe recompensas
                            Player::PlayerControl.setHP(100);
                            TextSplash* t = new TextSplash(pos.x, pos.y, 155,0,0, "HP Restored!");
                            t->addLists();
                            updateQuestState();
                        }else if(questState==QUEST_INACTIVE){
                            Quest::QuestList[quest]->setActive(true);
                            updateQuestState();
                        }
                    }
                    chat.setVisible(false);
                }
            }

        }
    }

    entidadeColidida.clear();
}

void NPC::setOffsetXMinus(int offX)
{
    offsetXMinus = offX;
}
void NPC::render(){
    Personagem::render();
    int r,g,b;
    r = 150;
    g = 44;
    b = 255;
    SDLBase::txt.applyText(pos.x-Camera::CameraControl.getX()-offsetXMinus, pos.y-Camera::CameraControl.getY()-10, 12, r,g,b, nome.c_str());
}
void NPC::update(unsigned int dt)
{
    Personagem::update(dt);
    chat.setPos(pos.x-80-Camera::CameraControl.getX(), pos.y-10-Camera::CameraControl.getY());
    //Se deixou ou não está colidindo com player
    if(entidadeColidida.empty()){
        chat.setVisible(false);
        chat.resetPage();
        Player::PlayerControl.canShot = true;
    }
}

//Muda o comportamento para que só tente colidir com o player
bool NPC::isValidPosition(int newX, int newY, float goX, float goY)
{
    //return Entidade::isValidPosition(newX,newY,goX,goY);

    bool Return = true;

    //Pega indexes dos Tiles que precisam ser testados
    int startX =(newX + col_offset.x) / TILE_SIZE;
    int startY =(newY + col_offset.y) / TILE_SIZE;
    int endX = ( newX + col_offset.x + col_offset.w -1 ) / TILE_SIZE;
    int endY =( newY + col_offset.y  + col_offset.h - 1) / TILE_SIZE;

    for(int iY = startY;iY <= endY;iY++) {
		for(int iX = startX;iX <= endX;iX++) {
            Tile* tile = Map::MapControl.getTileFromIndex(iX, iY);

			if(isValidTile(tile) == false) {
				Return = false;
				break;
			}
		}
	}

	if(this->flags & ENTIDADE_FLAG_MAP_ONLY){


	} else {
        if(isColisaoEntidade((Entidade*)&Player::PlayerControl, newX, newY) ) {
            //Se tiver a flag, registra a colisão, porém, não para o objeto.
            if( (flags & ENTIDADE_FLAG_MAP_ONLY_COLIDE) != ENTIDADE_FLAG_MAP_ONLY_COLIDE )
                Return = false;
        }
	}

    return Return;

}

void NPC::updateQuestState(){
   // if(quest >= (int)Quest::QuestList.size()) return;
    //Se estiver DONE e atualizar, recebeu recompensas e completou a quest
    if(this->questState == QUEST_DONE){
        this->questState = QUEST_COMPLETE;
        return;
    }
    if(Quest::QuestList[quest]->isCompleted()) {
        this->questState=QUEST_DONE;
        this->chat=this->doneTxt;
        Quest::QuestList[quest]->setActive(false);
    }else if(Quest::QuestList[quest]->isActive()){
        this->questState=QUEST_INPROGRESS;
        this->chat=this->progressTxt;
    }else{
        this->questState=QUEST_INACTIVE;
        this->chat=this->startTxt;
    }
}
