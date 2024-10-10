#include "info.hpp"
#include "texture.hpp"

using namespace Ginfo::Texture;

static sf::Sprite* sprite = new sf::Sprite;
static sf::Texture *a_pTextures = new sf::Texture[TEXTURE_COUNT];


void loadTextures()
{
    a_pTextures[BLOCK_TEXTURE].loadFromFile("data/images/blocks.png");
    a_pTextures[PLAYER_TEXTURE].loadFromFile("data/images/Peef.png");
}

sf::Sprite& getSprite(
Ginfo::Entity::Type EntityType,
sf::Vector2f &pos,
Ginfo::Block::Type BlockType)
{
    sprite->setScale(1.f,1.f);
    if (EntityType == Ginfo::Entity::BLOCK)
    {
        sprite->setTexture(a_pTextures[BLOCK_TEXTURE]);
        sprite->setTextureRect(sf::IntRect(BLOCK_SIZE,0,BLOCK_SIZE,BLOCK_SIZE));
        sprite->setColor(sf::Color(255,255,255));
        sprite->setPosition(pos);
        return *sprite;
    }

    if (EntityType == Ginfo::Entity::SMALL_BLOCK)
    {
        sprite->setTexture(a_pTextures[BLOCK_TEXTURE]);
        sprite->setTextureRect(sf::IntRect(BLOCK_SIZE,0,BLOCK_SIZE,BLOCK_SIZE));
        sprite->setColor(sf::Color(255,255,255));
        sprite->setScale(1/9.f,1/9.f);
        sprite->setPosition(pos);
        return *sprite;
    }

    if (EntityType == Ginfo::Entity::ITEM)
    {

    }

    if (EntityType == Ginfo::Entity::MOB)
    {

    }

    if (EntityType == Ginfo::Entity::PLAYER)
    {
        sprite->setTexture(a_pTextures[PLAYER_TEXTURE]);
        sprite->setTextureRect(sf::IntRect(0,0,PLAYER_SPRITE_SIZE,PLAYER_SPRITE_SIZE));
        sprite->setOrigin(sf::Vector2f((float)(PLAYER_SPRITE_SIZE-PLAYER_SIZE)/2,
        (float)(PLAYER_SPRITE_SIZE-PLAYER_SIZE)/2));
        sprite->setPosition(pos);
        return *sprite;
    }
}