#include "moveimage.h"

MoveImage::MoveImage()
{
    ready = true;
    pos.x = 0;
    pos.y = 0;
    dir.x = 0;
    dir.y = 0;
}
void MoveImage::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}
void MoveImage::setPos(Vetor vPos)
{
    pos = vPos;
}
void MoveImage::update(unsigned int dt)
{
    if (actionList.empty() )
    {
        ready = true;
        return;
    } else
    {
        ready = false;
    }

    // se time == 0 então movimento.
    if(actionList.front().time == 0)
    {
        dir = (actionList.front().posTarget-pos);
        float inverseLenght = 1.0f/dir.lenght();
        dir = dir*inverseLenght;
        Vetor realVel = dir*(actionList.front().speed*(dt/1000.0f) ) ;

        //Se passar pela area de parada
        if(move(realVel.x, realVel.y) == false)
        {
            actionList.pop();
            countdown.start();
            dir.x = 0;
            dir.y = 0;
        }


        //pos = pos + dir*(actionList.front().speed*(dt/1000.0f) ) ;

    }
    else
    {
        if (countdown.getTime() > actionList.front().time)
        {
            actionList.pop();
            countdown.start();
            dir.x = 0;
            dir.y = 0;
        }

    }

}


//==============================================================================
// Realisa movimento... testa pixel por pixel e movimenta x e y independentes
// MoveX e MoveY já devem ser passádos apos o fatoramento dos ticks
bool MoveImage::move(float moveX, float moveY)
{
    if (moveX == 0 && moveY == 0) return true;

    double newX = 0;
    double newY = 0;


    // Pega valores para newX e newY
    // Case move seja maior doq 1, o incremento de teste será 1
    // Caso seja menor, o incremento será o próprio valor
    if(moveX != 0) {
        if(moveX > 1)
            newX = 1;
        else
        if(moveX < -1)
            newX = -1;
        else
            newX = moveX;
    }

    if(moveY != 0) {
        if(moveY > 1)
            newY = 1;
        else
        if(moveY < -1)
            newY = -1;
        else
            newY = moveY;
    }

    // A cada iteração irá testar colisões para os novos X e Y independentemente
    //caso haja colisão, zera a velocidade naquele eixo
    //
    while(true) {

        //Decrementa moveXY pelo newXY utilizado
        moveX += -newX;
        moveY += -newY;

        if(//Calcula aproximação se colide com area
           (pos.x+newX > actionList.front().posTarget.x-2) && (pos.x+newX < actionList.front().posTarget.x+2) &&
           (pos.y > actionList.front().posTarget.y-2) && (pos.y < actionList.front().posTarget.y+2)
           ) {
            return false;
        }
        else {
            pos.x += newX;
        }

        if(//Calcula aproximação se colide com area
           (pos.x+newX > actionList.front().posTarget.x-2) && (pos.x+newX < actionList.front().posTarget.x+2) &&
           (pos.y > actionList.front().posTarget.y-2) && (pos.y < actionList.front().posTarget.y+2)
           ) {
            return false;
        }
        else {
            pos.y += newY;
        }

        if(newX > 0 && moveX <= 0) newX = 0;
        if(newX < 0 && moveX >= 0) newX = 0;
        if(newY > 0 && moveY <= 0) newY = 0;
        if(newY < 0 && moveY >= 0) newY = 0;

        if (moveX == 0) newX = 0;
        if (moveY == 0) newY = 0;


        if(moveX == 0 && moveY 	== 0) 	break;//Retirar? somente o de baixo ja é suficiente?
		if(newX  == 0 && newY 	== 0) 	break;
    }

    return true; //conseguiu se mover, não colide com area.
}


void MoveImage::render()
{
    image->render(pos.x, pos.y);
}
void MoveImage::setSprite(Sprite* imageFile)
{
    pos.x = 0;
    pos.y = 0;
    image = imageFile;
}

void MoveImage::addMoveToXY(int x, int y, float fspeed)
{
    FrameInfo info;
    info.posTarget.x = x;
    info.posTarget.y = y;
    info.speed = fspeed;

    actionList.push(info);
}

void MoveImage::addMoveToXY(Vetor vpos, float fspeed)
{
    addMoveToXY(vpos.x, vpos.y, fspeed);
}

void MoveImage::addWaiting(unsigned int miliseconds)
{
    FrameInfo info;
    countdown.start();
    info.time = miliseconds;

    actionList.push(info);
}
void MoveImage::addSoundEffect(int soundID, bool wait)
{

}
bool MoveImage::isReady()
{
    return ready;
}
