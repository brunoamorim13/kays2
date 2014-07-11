//==============================================================================
#include "camera.h"
//==============================================================================

Camera Camera::CameraControl;


Camera::Camera()
{
    x = y = 0;
    targetX = targetY = 0;
    targetMode = TARGET_MODE_NORMAL;
}

//Pega a posição X
int Camera::getX()
{
    int posX;
    if (targetMode == TARGET_MODE_NORMAL)
        posX = x;
    else
        posX = (int)*targetX - (SCREEN_WIDTH/2);

    if (posX < 0 )
        posX = 0;

    if (posX > (Map::MapControl.map_width*TILE_SIZE-SCREEN_WIDTH) )
        posX = Map::MapControl.map_width*TILE_SIZE-SCREEN_WIDTH;
    return posX;
}

//Pega a posição y
int Camera::getY()
{
    int posY;
    if (targetMode == TARGET_MODE_NORMAL)
        posY = y;
    else
        posY = (int)*targetY - (SCREEN_HEIGHT/2);

    if (posY < 0 )
        posY = 0;

    if (posY > (Map::MapControl.map_height*TILE_SIZE-SCREEN_HEIGHT) )
        posY = Map::MapControl.map_height*TILE_SIZE-SCREEN_HEIGHT;

    return posY;
}

//Ajusta posição
void Camera::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

//Ajusta o alvo
void Camera::setTarget(float* targX, float* targY)
{
    targetX = targX;
    targetY = targY;
}

//Move a camera, sistema de coordenadas do SDL
void Camera::move(int moveX, int moveY)
{
    x+=moveX;
    y+=moveY;
}


