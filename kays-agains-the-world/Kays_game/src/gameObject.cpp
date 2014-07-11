#include "gameObject.h"

#include "camera.h"

GameObject::GameObject(int xPos, int yPos)
{
    this->pos.x = xPos;
    this->pos.y = yPos;
    col_offset.x = col_offset.y = col_offset.h = col_offset.w = 0;
    showCollision = false;
}

GameObject::GameObject()
{
    col_offset.x = col_offset.y = col_offset.h = col_offset.w = 0;
    showCollision = false;
}
GameObject::GameObject(int xPos, int yPos, int wCol, int hCol)
{
    pos.x = xPos;
    pos.y = yPos;
    setCollisionBox(xPos,yPos,wCol,hCol);
    showCollision = false;
    entityID = 0;
}
void GameObject::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}
void GameObject::setCollisionBox(int x, int y, int w, int h)
{
    col_offset.x = x;
    col_offset.y = y;
    col_offset.w = w;
    col_offset.h = h;
}
Rect GameObject::getCollisionBox()
{
    return col_offset;
}
bool GameObject::isCollision(GameObject* other)
{
    if (other == 0 || this == other) return false;
    if(dead || other->dead) return false;
    Rect dif;
    dif.x = pos.x+col_offset.x - (other->pos.x+other->col_offset.x);
    dif.y = pos.y+col_offset.y - (other->pos.y+other->col_offset.y);

    if(dif.x > other->col_offset.w || -dif.x > col_offset.w) return false;
    if(dif.y > other->col_offset.h || -dif.y > col_offset.h) return false;

    return true;
}

void GameObject::getRelativePos(int& ix, int& iy){

    ix = (pos.x - Camera::CameraControl.getX() ) / TILE_SIZE;
    iy = (pos.y - Camera::CameraControl.getY() ) / TILE_SIZE;

}
