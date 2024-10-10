#include <SFML/Graphics.hpp>
#include "info.hpp"

void loadTextures();

sf::Sprite& getSprite(
Ginfo::Entity::Type EntityType,
sf::Vector2f &pos,
Ginfo::Block::Type BlockType = Ginfo::Block::STONE);