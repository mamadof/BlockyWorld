#include "game.hpp"
#include "gameWorld.hpp"
#include "share.hpp"
#include "texture.hpp"
#include "math.hpp"
#include "imgui-sfml/imgui-SFML.h"

extern CPlayer* pPlayer;

static void drawPlayerInventory();

void CGame::render()
{
    sf_window.clear(sf::Color(200,200,200,255));
    //draw border
    sf_window.draw(pworld->m_border);
    //draw player
    sf_window.draw(getSprite(Ginfo::Entity::PLAYER, pworld->player()->m_pos));
    // sf::RectangleShape playerRect;
    // playerRect.setSize(sf::Vector2f(PLAYER_SIZE,PLAYER_SIZE));
    // playerRect.setPosition(pworld->player()->m_pos);
    // sf_window.draw(playerRect);
    //draw blocks
    CCell* pCell;
    for (int x = 0; x < pworld->m_width; x++)
    {
        for (int y = 0; y < pworld->m_height; y++)
        {
            pCell = pworld->getCell(x*GRID_SIZE, y*GRID_SIZE);
            CBlock *pblock = &pCell->m_BlockContent;
            if (!pblock->m_deleted)
            {
                if (pblock->m_type != Ginfo::Block::MIXED)
                {
                    sf_window.draw(
                    getSprite(Ginfo::Entity::BLOCK, pblock->m_pos, pblock->m_type));
                }
                //show small blocks if block type is mixed
                if(pblock->m_type == Ginfo::Block::MIXED)
                {
                    CSmallBlock *pSmallBlock;
                    for (int x = 0; x < BLOCK_SUBDIVISION; x++)
                    {
                        for (int y = 0; y < BLOCK_SUBDIVISION; y++)
                        {
                            pSmallBlock = &pblock->ma_SmallBlocks[x][y];
                            if (pSmallBlock->m_deleted)continue;
                            sf_window.draw(getSprite(
                            Ginfo::Entity::SMALL_BLOCK,
                            pSmallBlock->m_pos,
                            pSmallBlock->m_type));
                        }
                    }
                }
            }
            if (pCell->m_DropItems.size() > 0)
            {
                for (int x = 0; x < pCell->m_DropItems.size(); x++)
                {
                    sf_window.draw(getDropItemSprite(pCell->m_DropItems.at(x)));
                }
            }
        }
    }
    //block shadow
    // sf_window.draw(blockShadow);
    sf_window.draw(getSprite(
    pworld->player()->m_rightHand.m_itemType,
    gm::snapToGrid(m_mousePosWorld),
    Ginfo::Block::Type(pworld->player()->m_rightHand.m_itemID)));
    //debuging stuff
    sf_window.draw(m_debugText);
    ImGui::SFML::Render(sf_window);
    if (pworld->player()->m_isInventoryOpen)
    {
        drawPlayerInventory();
    }
    sf_window.display();
}

static void drawPlayerInventory()//inventory gui is rendered in gui.cpp
{
    sf_window.setView(sf_window.getDefaultView());

    float padding = 3;
    sf::RectangleShape bigRect(sf::Vector2f(
        ITEM_CONTAINER_SIZE * 9 + padding * 9*2,
        ITEM_CONTAINER_SIZE * 3 + padding * 3*2
        ));

    bigRect.setFillColor(sf::Color(160,160,160));
    bigRect.setPosition(
        300,
        ((float)sf_window.getSize().y/2) - bigRect.getSize().y/2
    );
    sf_window.draw(bigRect);

    sf::RectangleShape smallRect(sf::Vector2f(ITEM_CONTAINER_SIZE,ITEM_CONTAINER_SIZE));
    smallRect.setFillColor(sf::Color(120,120,120));
    sf::Vector2f sPos(bigRect.getPosition());

    for (int y = 0; y < 3; y++)
    {
        sPos.y += padding;
        for (int x = 0; x < 9; x++)
        {
            sPos.x += padding;
            smallRect.setPosition(sPos);
            sf_window.draw(smallRect);

            if (pPlayer->m_inventory[y*9 + x].m_count != 0)
            {
                sf::Sprite* sprite = &getSprite(
                pPlayer->m_inventory[y*9 + x].m_type,
                sf::Vector2f(0,0),
                pPlayer->m_inventory[y*9 + x].m_typeID);
                sprite->setScale(
                sf::Vector2f(
                (float)ITEM_CONTAINER_SPRITE_SIZE/BLOCK_SIZE,
                (float)ITEM_CONTAINER_SPRITE_SIZE/BLOCK_SIZE));
                sprite->setPosition(smallRect.getPosition());
                sf_window.draw(*sprite);
            }

            sPos.x += padding;
            sPos.x += ITEM_CONTAINER_SIZE;
        }
        sPos.x = bigRect.getPosition().x;
        sPos.y += padding;
        sPos.y += ITEM_CONTAINER_SIZE;

    }
    sf_window.setView(pPlayer->m_view);
}
