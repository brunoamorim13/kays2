#pragma once

#include "vetor.h"

class Rect
{
    public:
        int x,y;
        int w,h;
        Rect(int fx = 0, int fy = 0, int fw = 0, int fh = 0) : x(fx), y(fy), w(fw), h(fh) {}

};

class GameObject
{
    public:
        int entityID;
        Vetor pos;
        Rect col_offset;
        bool dead;
        bool showCollision;

        GameObject(int xPos, int yPos);
        GameObject(int xPos, int yPos, int wCol,int hCol);
        GameObject();

        bool isCollision(GameObject* other);
        void setPos(float x, float y);

        void getRelativePos(int& ix, int& iy);

        void setCollisionBox(int x, int y, int w, int h);
        Rect getCollisionBox();
};
