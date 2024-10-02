#include "share.hpp"
#include "input.hpp"

using namespace Input;
static KeyState a_keyState[GameKeys::KEYS_COUNT] = {KeyState::NONE};
static long a_keyBinds[GameKeys::KEYS_COUNT] = {sf::Keyboard::Scancode::Unknown};
static bool a_isKeyMouse[GameKeys::KEYS_COUNT] = {false};


void Input::handleInput()
{
    for (int i = 0; i < KEYS_COUNT; i++)
    {
        if(!a_isKeyMouse[i])
        {
            if(sf::Keyboard::isKeyPressed((sf::Keyboard::Scancode)a_keyBinds[i]))
            {
                a_keyState[i] = Input::KeyState::PRESSED;
            }else{
                if (a_keyState[i] == Input::KeyState::PRESSED)
                {
                    a_keyState[i] = Input::KeyState::RELEASED;
                }else{
                    a_keyState[i] = Input::KeyState::NONE;
                }
            }
        }else {
            if(sf::Mouse::isButtonPressed((sf::Mouse::Button)a_keyBinds[i]))
            {
                a_keyState[i] = Input::KeyState::PRESSED;
            }else{
                if (a_keyState[i] == Input::KeyState::PRESSED)
                {
                    a_keyState[i] = Input::KeyState::RELEASED;
                }else{
                    a_keyState[i] = Input::KeyState::NONE;
                }
            }
            
        }
    }
}

void Input::setKeyBind(GameKeys key, long sf_Scancode, bool isMouse)
{
    a_keyBinds[key] = sf_Scancode;
    a_isKeyMouse[key] = isMouse;
}

void Input::setGameKeyState(GameKeys key, KeyState state)
{
    a_keyState[key] = state;
}

long Input::getKeyBind(GameKeys key)
{
    return a_keyBinds[key];
}

unsigned short Input::getGameKeyState(GameKeys key)
{
    return a_keyState[key];
}

bool Input::isKeyMouse(GameKeys key)
{
    return a_isKeyMouse[key];
}

