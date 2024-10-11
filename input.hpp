#ifndef INPUT_HPP
#define INPUT_HPP
#include <SFML/Window.hpp>

namespace Input{
    typedef enum{
        UP,
        DOWN,
        STATE_COUNT
    }KeyState;

    typedef enum{
        SCROLL_UP = 1,
        SCROLL_DOWN = -1
    }MouseScroll;

    typedef enum{
        KEYBOARD,
        MOUSE,
        MOUSE_WHEEL,
        KEY_TYPE_COUNT
    }KeyType;

    enum GameKeys{
        LMB,//left mouse button
        RMB,//right mouse button
        JUMP,
        A,
        D,
        W,
        S,
        ZOOM_IN,
        ZOOM_OUT,
        TOOLBAR_NEXT,
        TOOLBAR_PREV,
        QUIT,
        GAME_KEYS_COUNT
    };
};
void handleInput();//don't call this by your own, it's pointless
void setKeyBind(Input::GameKeys key, long sf_Scancode, Input::KeyType KeyType);
Input::KeyState &getKeyState(Input::GameKeys key);
long &getKeyBind(Input::GameKeys key);
Input::KeyType &getKeyType(Input::GameKeys key);
bool isKeyPressed(Input::GameKeys key);
bool isKeyReLeased(Input::GameKeys key);
bool isKeyDown(Input::GameKeys key);
static void resetKeyBools();
void unloadInput();

#endif //INPUT_HPP