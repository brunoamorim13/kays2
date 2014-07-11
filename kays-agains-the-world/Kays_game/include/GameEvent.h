#pragma once

#include "gameObject.h"


class GameEvent : public GameObject {

public:

    int EventID;

    bool isTriggered();
    bool isActive();
    void setActive(bool active);
private:
    bool EventActive;
    bool EventTriggered;
};

class GameData : public GameObject {
public:


};
