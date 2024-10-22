#include "info.hpp"
#include "texture.hpp"
#include "gameWorld.hpp"

using namespace Ginfo::Texture;

static sf::Sprite sprite;
static sf::Texture a_pTextures[TEXTURE_COUNT];


void loadTextures()
{
    a_pTextures[BLOCK_TEXTURE].loadFromFile("data/images/blocks.png");
    a_pTextures[PLAYER_TEXTURE].loadFromFile("data/images/player.png");
}

sf::Sprite& getSprite(
Ginfo::Entity::Type EntityType,
sf::Vector2f pos,
long typeID,
long DropItemType)
{
    sprite.setScale(1.f,1.f);
    sprite.setColor(sf::Color(255,255,255));
    sprite.setOrigin(0,0);
    if (EntityType == Ginfo::Entity::BLOCK)
    {
        sprite.setTexture(a_pTextures[BLOCK_TEXTURE]);
        sprite.setTextureRect(sf::IntRect(
        (typeID * BLOCK_SIZE) % (BLOCK_SIZE * 10),
        ((typeID * BLOCK_SIZE) / (BLOCK_SIZE * 10)) * BLOCK_SIZE,
        BLOCK_SIZE,BLOCK_SIZE));
        sprite.setPosition(pos);
        return sprite;
    }

    if (EntityType == Ginfo::Entity::SMALL_BLOCK)
    {
        sprite.setTexture(a_pTextures[BLOCK_TEXTURE]);
        sprite.setTextureRect(sf::IntRect(
        (typeID * BLOCK_SIZE) % (BLOCK_SIZE * 10),
        ((typeID * BLOCK_SIZE) / (BLOCK_SIZE * 10)) * BLOCK_SIZE,
        BLOCK_SIZE,BLOCK_SIZE));
        sprite.setScale(1/9.f,1/9.f);
        sprite.setPosition(pos);
        return sprite;
    }

    if (EntityType == Ginfo::Entity::ITEM)
    {

    }

    if (EntityType == Ginfo::Entity::MOB)
    {

    }

    if (EntityType == Ginfo::Entity::PLAYER)
    {
        sprite.setTexture(a_pTextures[PLAYER_TEXTURE]);
        sprite.setTextureRect(sf::IntRect(0,0,PLAYER_SPRITE_SIZE,PLAYER_SPRITE_SIZE));
        sprite.setOrigin(sf::Vector2f((float)(PLAYER_SPRITE_SIZE-PLAYER_SIZE)/2,
        (float)(PLAYER_SPRITE_SIZE-PLAYER_SIZE)/2));
        sprite.setPosition(pos);
        return sprite;
    }
    printf("what did you did ? -__-\n");
}

sf::Sprite& getDropItemSprite(CDropItem* pDropItem)
{
    getSprite(pDropItem->m_type, pDropItem->m_pos, pDropItem->m_typeID);
    sprite.setScale(
    (float)(DROP_ITEM_SIZE+pDropItem->m_count)/BLOCK_SIZE,
    (float)(DROP_ITEM_SIZE+pDropItem->m_count)/BLOCK_SIZE);
    sprite.setPosition(pDropItem->m_pos);
    return sprite;
}

// sf::Sprite& getItemContainerSprite(CItemContainer* pItemCon)
// {
//     getSprite(pItemCon->m_type, sf::Vector2f pos)
// }

