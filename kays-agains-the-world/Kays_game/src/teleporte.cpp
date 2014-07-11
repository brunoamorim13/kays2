#include "teleporte.h"

std::vector<Teleporte*> Teleporte::TeleporteList;

Teleporte::Teleporte(std::string filename, int x, int y, int w, int h, int desX, int desY) : GameObject::GameObject(x,y,w,h)
{
    sameMap = false;
    nome_map = filename;
    showCollision = true;
    destPos.x = desX;
    destPos.y = desY;
    col_offset.x = col_offset.y = 0;
    dead = false;

}
Teleporte::Teleporte(int x, int y, int w, int h, int desX, int desY, int times) : GameObject::GameObject(x,y,w,h)
{
    sameMap = true;
    showCollision = true;
    timesUse = times;
    destPos.x = desX;
    destPos.y = desY;
    col_offset.x = col_offset.y = 0;
    dead = false;
}

void Teleporte::render()
{
    if(showCollision) {
        boxRGBA(SDLBase::getScreen(),
                    pos.x+col_offset.x-Camera::CameraControl.getX(), pos.y+col_offset.y-Camera::CameraControl.getY(),
                    pos.x+col_offset.x+col_offset.w-Camera::CameraControl.getX(), pos.y+col_offset.y+col_offset.h-Camera::CameraControl.getY(),
                    200, 0, 0, 50 );
    }
}
void Teleporte::update(GameObject* player)
{
    //Se colide com o player
    if(this->isCollision(player) == true)
    { //Reporta pro mapa para mudar de mapa
        if(sameMap == false){
            Map::MapControl.setMap(nome_map);
        }
        //Não importa oq houver, se houver colisão, teleporta
        player->setPos(this->destPos.x, this->destPos.y);

        //-1 significa teleporte infinito
        if(timesUse == -1)
        {
            return;
        }
        //Se mesmo mapa e ainda tiver usos, retorna e não deleta teleporte.......
        if(sameMap == true && timesUse > 0)
        {
            timesUse--;
            return;
        }
        //Remove este teleporte
        destroy();

    }
}
// Se remove da lista e se deleta ------------------------------------------------
void Teleporte::destroy()
{
    for(unsigned int i = 0; i < TeleporteList.size();i++)
        {
            if (TeleporteList[i] == this)
            {
                TeleporteList.erase(TeleporteList.begin()+ i);
                delete (this);
            }
        }
}
void Teleporte::addLists()
{
    TeleporteList.push_back(this);
}
