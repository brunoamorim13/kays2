#pragma once

#define N_KEYS 512
#define N_MOUSE_BUTTONS 3
#define DEAD_ZONE 8200
#define N_JOYBUTTONS 14

#include <SDL/SDL.h>
#include<vector>

using std::vector;
using std::pair;
class InputManager {
    private:
        static InputManager *instance;


        Uint8 mouse, *teclado;
        Uint8 *joystick;
        bool keyDown[N_KEYS], keyUp[N_KEYS];
        bool quitGame;
        bool axisDown[2], axisUp[2];
        Uint8 mouseDown[N_MOUSE_BUTTONS], mouseUp[N_MOUSE_BUTTONS];
        int mouseX, mouseY;
        bool numberJoysticks;
        Uint8 joyButtonDown[N_JOYBUTTONS], joyButtonUp[N_JOYBUTTONS];
        vector<SDL_Joystick*> joysticks;
        vector< vector<bool> > buttonStates;
        void onJoystickButtonDown(SDL_Event& event);
        void onJoystickButtonUp(SDL_Event& event);
        void onJoystickMotion(SDL_Event& event);
        int buttonNumber;
        int axisNumber;

        int directionX;
        int directionY;


    public:

        int getDirectionX();
        // -1 default, 0 direita, 1 esquerda
        int getDirectionY();
        // -1 default, 0 cima


        InputManager();

        void initializeJoysticks();
        static InputManager* getInstance();
        void Update();
        bool isKeyDown(int key = -1);
        bool isKeyUp(int key = -1);
        bool isKeyPressed(int key = -1);
        bool isMouseDown(int button);
        bool isMouseUp(int button);
        bool isMousePressed(int button);
        bool joysticksInitialized () {return numberJoysticks;}

        bool getButtonState(int joy, int buttonNumber){
            if(joysticks.size()<1)
                return false;
            return SDL_JoystickGetButton(joysticks[0], buttonNumber);}
        bool getAxisState(int joy, int axisNumber)
        {
            if(joysticks.size() < 1)
                return false;
            return SDL_JoystickGetAxis(joysticks[0], axisNumber);
        }
        bool isJoyButtonDown(int button = -1);
        bool isJoyButtonUp(int button = -1);
        //bool isJoyButtonPressed(int button = -1);

        int mousePosX();
        int mousePosY();
        bool isMouseInside(SDL_Rect* rect);
        bool QuitGame();


        int yValue (int joy, int stick);
};


