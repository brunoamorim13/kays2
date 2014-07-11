#include "GameEvent.h"



bool GameEvent::isActive(){
    return EventActive;
}
void GameEvent::setActive(bool active){
    EventActive = active;
}
bool GameEvent::isTriggered(){
    return EventTriggered;
}
