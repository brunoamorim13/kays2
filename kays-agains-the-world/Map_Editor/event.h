#ifndef VIRTUAL_EVENT_H_
#define VIRTUAL_EVENT_H_

class EventHolder
{
    public:
        EventHolder(){}

        virtual void handleMouse(){}
        virtual void handleKeyboard(){}

        virtual void Render(){}
};

#endif
