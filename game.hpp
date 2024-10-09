#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "share.hpp"

class CGame{
    public:
    enum Textures{
        BLOCK_TEXTURE,
        PLAYER_TEXTURE,
        TEXTURE_COUNT
    };
    void run();
    sf::Vector2i m_mousePos;
    sf::Vector2i m_mousePosWorld;
    sf::Font m_font;
    sf::Text m_debugText;
    std::string m_debugString;
    sf::View m_renderView;
    sf::Texture m_aTextures[TEXTURE_COUNT];
    sf::Sprite m_Sprites;
    sf::Sprite &getSprite(gt::entity::Entity_Type EntityType, void *pEntity);
    int m_fps;

    private:
    void init();
    void tick();
    void render();
    void close();
};
#endif //GAME_HPP