#ifndef INPUT_HPP
#define INPUT_HPP
#include <SFML/Window.hpp>

namespace Input{
    enum KeyState{
        NONE,
        PRESSED,
        RELEASED,
        STATE_COUNT
    };
    enum GameKeys{
        LMB,//left mouse button
        RMB,//right mouse button
        JUMP,
        A,
        D,
        W,
        S,
        KEYS_COUNT
    };

    void handleInput();//don't call this by your own, it's pointless
    void setKeyBind(GameKeys key, long sf_Scancode, bool isMouse = false);
    void setGameKeyState(GameKeys key, KeyState state);
    bool isKeyMouse(GameKeys key);
    unsigned short getGameKeyState(GameKeys key);
    long getKeyBind(GameKeys key);
};

#endif //INPUT_HPP