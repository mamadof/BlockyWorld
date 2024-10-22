#include "share.hpp"
#include "input.hpp"
#include "imgui-sfml/imgui-SFML.h"
#include "imgui/imgui.h"
#include "game.hpp"
#include <iostream>

typedef struct{
    Input::KeyState m_keyState;
    Input::KeyType m_KeyType;
    long m_bind;
    bool m_pressed;
    bool m_released;
}Key;
static Key a_Keys[Input::GameKeys::GAME_KEYS_COUNT];
static Key* key;

static sf::Event sf_event;

void handleInput()
{
    resetKeyBools();
    while (sf_window.pollEvent(sf_event))
    {
        ImGui::SFML::ProcessEvent(sf_window, sf_event);
        if (sf_event.type == sf::Event::Closed)
        {
            pgame->close();
        }
        if (sf_event.type == sf::Event::KeyPressed)
        {
            for (int x = 0; x < Input::GAME_KEYS_COUNT; x++)
            {
                if (a_Keys[x].m_KeyType != Input::KEYBOARD)continue;
                if (a_Keys[x].m_bind != sf_event.key.scancode)continue;
                a_Keys[x].m_pressed = true;
                a_Keys[x].m_keyState = Input::DOWN;
            }
        }
        if (sf_event.type == sf::Event::KeyReleased)
        {
            for (int x = 0; x < Input::GAME_KEYS_COUNT; x++)
            {
                if (a_Keys[x].m_KeyType != Input::KEYBOARD)continue;
                if (a_Keys[x].m_bind != sf_event.key.scancode)continue;
                a_Keys[x].m_released = true;
                a_Keys[x].m_keyState = Input::UP;
            }
        }
        if (sf_event.type == sf::Event::MouseButtonPressed)
        {
            for (int x = 0; x < Input::GAME_KEYS_COUNT; x++)
            {
                if (a_Keys[x].m_KeyType != Input::MOUSE)continue;
                if (a_Keys[x].m_bind != sf_event.mouseButton.button)continue;
                a_Keys[x].m_pressed = true;
                a_Keys[x].m_keyState = Input::DOWN;
            }
        }
        if (sf_event.type == sf::Event::MouseButtonReleased)
        {
            for (int x = 0; x < Input::GAME_KEYS_COUNT; x++)
            {
                if (a_Keys[x].m_KeyType != Input::MOUSE)continue;
                if (a_Keys[x].m_bind != sf_event.mouseButton.button)continue;
                a_Keys[x].m_released = true;
                a_Keys[x].m_keyState = Input::UP;
            }
        }
        if (sf_event.type == sf::Event::EventType::MouseWheelScrolled)
        {
            for (int x = 0; x < Input::GAME_KEYS_COUNT; x++)
            {
                if (a_Keys[x].m_KeyType != Input::MOUSE_WHEEL)continue;
                if (a_Keys[x].m_bind != sf_event.mouseWheelScroll.delta)continue;
                a_Keys[x].m_pressed = true;
            }
        }
    }
}

void setKeyBind(Input::GameKeys key, long sf_Scancode, Input::KeyType KeyType)
{
    a_Keys[key].m_bind = sf_Scancode;
    a_Keys[key].m_KeyType = KeyType;
}
Input::KeyState &getKeyState(Input::GameKeys key)
{
    return a_Keys[key].m_keyState;
}
long &getKeyBind(Input::GameKeys key)
{
    return a_Keys[key].m_bind;
}
Input::KeyType &getKeyType(Input::GameKeys key)
{
    return a_Keys[key].m_KeyType;
}
bool isKeyPressed(Input::GameKeys key)
{
    return a_Keys[key].m_pressed;
}
bool isKeyReLeased(Input::GameKeys key)
{
    return a_Keys[key].m_released;
}
bool isKeyDown(Input::GameKeys key)
{
    return a_Keys[key].m_keyState == Input::DOWN;
}
static void resetKeyBools()
{
    for (int x = 0; x < Input::GAME_KEYS_COUNT; x++)
    {
        a_Keys[x].m_pressed = false;
        a_Keys[x].m_released = false;
    }
}



