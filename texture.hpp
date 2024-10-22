#include <SFML/Graphics.hpp>
#include "info.hpp"
#include "gameWorld.hpp"

void loadTextures();

sf::Sprite& getSprite(
Ginfo::Entity::Type EntityType,
sf::Vector2f pos,
long type_ID = 0,
long DropItemType = Ginfo::Entity::SMALL_BLOCK);

sf::Sprite& getDropItemSprite(CDropItem* dropItem);

sf::Sprite& getItemContainerSprite(CItemContainer* pItemCon);