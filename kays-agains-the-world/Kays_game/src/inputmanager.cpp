#include "inputmanager.h"
#include <iostream>

using namespace std;

InputManager* InputManager::instance;

InputManager* InputManager::getInstance()
{
    if (!instance)
    {
        instance = new InputManager();
    }

    return instance;
}

InputManager::InputManager(){

    for(int i = 0; i < N_KEYS; i++) {
        keyDown[i] = false;
        keyUp[i] = false;
    }
    for (int i = 0; i < N_MOUSE_BUTTONS; i++){
        mouseDown[i] = false;
        mouseUp[i] = false;
    }

    teclado = SDL_GetKeyState(NULL);
    mouse = SDL_GetMouseState(NULL,NULL);
    //joystick = SDL_JoystickGetButton(0,NULL);
    quitGame = false;

    initializeJoysticks();
}

void InputManager::initializeJoysticks()
 {
 	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
 	{
 		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
 	}

 if (SDL_NumJoysticks() > 0)
 	{
 		for (int i = 0; i < SDL_NumJoysticks(); i++)
 		{
 			SDL_Joystick* joy = SDL_JoystickOpen(i);

 			if (joy)
 			{
 				joysticks.push_back(joy);
 				//joystickValues.push_back(make_pair(new Vector2D(0,0), new Vector2D(0,0)));//Adds a pair
 				vector<bool> tempButtons;
 				int buttonCount = SDL_JoystickNumButtons(joy);
 				cout << "Controller 1 has: " << buttonCount << " Buttons." << endl;

 				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
 				{
 					tempButtons.push_back(false);
 				}
//
// 				for (int j = 0; j < SDL_JoystickNumAxes(joy); j++)
// 				{
////                    stick[i] = j;
// 				}

 				buttonStates.push_back(tempButtons);
 			}
 			else
 			{
 				cout << SDL_GetError() << endl;
 			}
 		}
 		SDL_JoystickEventState(SDL_ENABLE);
 		numberJoysticks = true;

 		cout << "Initialized " << joysticks.size() << " joystick(s)" << endl;
 	}
 	else
 	{
 		numberJoysticks = false;
 	}
 }

int InputManager::getDirectionX()
{
    return directionX;
}

int InputManager::getDirectionY()
{
    return directionY;
}

void InputManager::onJoystickButtonDown(SDL_Event &event)
{
	if (event.type == SDL_JOYBUTTONDOWN)
		{
			int whichOne = event.jaxis.which;

			buttonStates[whichOne][event.jbutton.button] = true;
			cout << event.jbutton.button << endl;
		}
}

void InputManager::onJoystickButtonUp(SDL_Event &event)
{
	if (event.type == SDL_JOYBUTTONUP)
		{
			int whichOne = event.jaxis.which;

			buttonStates[whichOne][event.jbutton.button] = false;
		}
}

bool InputManager::isJoyButtonDown(int button)
{
    if(button == -1)
    {
        for(unsigned int i = 0; i < buttonStates.size();i++) {
            if(joyButtonDown[i])
                return true;
        }
        return false;
    }
    return joyButtonDown[button];
}

bool InputManager::isJoyButtonUp(int button)
{
    if(button == -1)
    {
        for(unsigned int i = 0; i < buttonStates.size();i++) {
            if(joyButtonUp[i])
                return true;
        }
        return false;
    }
    return joyButtonUp[button];
}

//int InputManager::xValue(int joy, int stick[])
//{
//    if (SDL_JoystickNumAxes(0))
//	{
//		if (stick == 0)
//		{
//            cout << stick[0] << endl;
//			return joystickValues[joy].first->getX();
//		}
//		else if (stick == 1)
//		{
//			return joystickValues[joy].second->getX();
//		}
//	}
//return 0;
//}
//
//int InputManager::yValue(int joy, int stick)
//{
//    if(stick == 1)
//        return 0;
//}

//bool InputManager::isJoyButtonPressed(int button){
//    if(button == -1)
//    {
//        for(int i = 0; i < N_JOYBUTTONS;i++) {
//            if(joystick[i])
//                return true;
//        }
//        return false;
//    }
//    return joystick[button];
//}

void InputManager::onJoystickMotion(SDL_Event& event)
{
//If joystick 0 has moved
    if( event.jaxis.which == 0 )
    {
        //If the X axis changed
        if( event.jaxis.axis == 0 )
        {
            //If the X axis is neutral
            if( ( event.jaxis.value > -DEAD_ZONE ) && ( event.jaxis.value < DEAD_ZONE ) )
            {
                directionX = -1;
            }
            //If not
            else
            {
                //Adjust the velocity
                if( event.jaxis.value < DEAD_ZONE )
                {
                    directionX = 1;
                }
                else
                {
                    directionX = 0;
                }
            }
        }
        //If the Y axis changed
        else if( event.jaxis.axis == 1 )
        {
            //If the Y axis is neutral
            if( ( event.jaxis.value > -DEAD_ZONE ) && ( event.jaxis.value < DEAD_ZONE ) )
            {
                directionY = -1;
            }
            //If not
            else
            {
                //Adjust the velocity
                if( event.jaxis.value < DEAD_ZONE )
                {
                    directionY = 0;
                }
                else
                {
                    directionY = 1;
                }
            }
        }
    }
}

void InputManager::Update()
{
    for(int i = 0; i < N_KEYS; i++) {
        keyDown[i] = false;
        keyUp[i] = false;
    }
    for (int i = 0; i < N_MOUSE_BUTTONS; i++){
        mouseDown[i] = false;
        mouseUp[i] = false;
    }
    for (int i = 0; i < N_JOYBUTTONS; i++)
    {
        joyButtonDown[i] = false;
        joyButtonUp[i] = false;
    }
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        mouse = SDL_GetMouseState(NULL,NULL);
        teclado = SDL_GetKeyState(NULL);
        //joystick = SDL_JoystickGetButton(NULL,NULL);


        switch (event.type) {
        case SDL_KEYDOWN:
            keyDown[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keyUp[event.key.keysym.sym] = true;
            break;
        case SDL_JOYBUTTONDOWN:
            joyButtonDown[event.jbutton.button] = true;
			break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
			break;
        case SDL_JOYAXISMOTION:
            onJoystickMotion(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseDown[event.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseUp[event.button.button] = true;
            break;
        case SDL_MOUSEMOTION:
            mouseX = event.button.x;
            mouseY = event.button.y;
            mouse = event.button.state;
            break;
        case SDL_QUIT:
            quitGame = true;
            break;
        default:;
        }
    }
}
bool InputManager::isKeyDown(int key){
    if(key == -1)
    {
        for(int i = 0; i < N_KEYS;i++) {
            if(keyDown[i])
                return true;
        }
        return false;
    }
    return keyDown[key];

}
bool InputManager::isKeyUp(int key){
    if(key == -1)
    {
        for(int i = 0; i < N_KEYS;i++) {
            if(keyUp[i])
                return true;
        }
        return false;
    }

    return keyUp[key];
}
bool InputManager::isKeyPressed(int key){
    if(key == -1)
    {
        for(int i = 0; i < N_KEYS;i++) {
            if(teclado[i])
                return true;
        }
        return false;
    }
    return teclado[key];
}
bool InputManager::isMouseDown(int button){
    return mouseDown[button];
}
bool InputManager::isMouseUp(int button){
    return mouseUp[button];
}
//Use 1 para esquerdo, 2 meio e 3 direito
bool InputManager::isMousePressed(int button){
    return mouse&SDL_BUTTON(button);
}
int InputManager::mousePosX(){
    return mouseX;
}
int InputManager::mousePosY(){
    return mouseY;
}
bool InputManager::isMouseInside(SDL_Rect* rect){
    if (mouseX> rect->x && (mouseX < (rect->x+rect->w)) )
        if (mouseY > rect->y && (mouseY < (rect->y+rect->h)) )
            return true;
    return false;
}
bool InputManager::QuitGame(){
    return quitGame;
}



