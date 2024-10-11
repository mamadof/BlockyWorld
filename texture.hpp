#include <SFML/Graphics.hpp>
#include "info.hpp"

void loadTextures();

sf::Sprite& getSprite(
Ginfo::Entity::Type EntityType,
sf::Vector2f pos,
long type_ID = 0,
long DropItemType = Ginfo::Entity::SMALL_BLOCK);