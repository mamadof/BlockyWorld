#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

class CGame{
    public:
    void run();
    sf::Vector2i m_mousePos;
    sf::Vector2i m_mousePosWorld;
    sf::RectangleShape m_border;
    sf::Font m_font;
    sf::Text m_debugText;
    std::string m_debugString;
    int m_fps;

    private:
    void init();
    void tick();
    void render();
    void close();
};
//helper functions
sf::Vector2i snapToGrid(int x, int y);
sf::Vector2i snapToGrid(sf::Vector2i);
sf::Vector2i snapToGrid(sf::Vector2f);
#endif //GAME_HPP