//==============================================================================
#pragma once


#include "defines.h"
#include "map.h"
//==============================================================================

enum
{
    TARGET_MODE_CENTER = 0,
    TARGET_MODE_NORMAL
};

class Camera
{
    public:
        static Camera CameraControl;

    private:
        int x;
        int y;

        float* targetX;
        float* targetY;

    public:
        int targetMode;

        Camera();

        int getX();
        int getY();

        void setTarget(float* targX, float* targY);
        void setPos(int x, int y);

        void move(int moveX, int moveY);


};

//==============================================================================


