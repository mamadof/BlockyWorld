#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "share.hpp"
#include "info.hpp"

class CGame{
    public:
    void run();
    sf::Vector2i m_mousePos;
    sf::Vector2i m_mousePosWorld;
    sf::Font m_font;
    sf::Text m_debugText;
    std::string m_debugString;
    sf::View m_renderView;
    int m_fps;

    private:
    void init();
    void tick();
    void render();
    void close();
};
#endif //GAME_HPP