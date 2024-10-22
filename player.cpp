#include "share.hpp"
#include "gameWorld.hpp"
#include "input.hpp"
#include "math.hpp"
#include "game.hpp"
#include "info.hpp"

CPlayer::CPlayer()
{
    m_pos = sf::Vector2f(0,0);
    m_HP = 50;
    m_maxHP = 50;
    m_velocity = sf::Vector2f(0,0);
    m_force = sf::Vector2f(0,0);
    m_grounded = false;
    m_flying = false;
    m_rubbing = false;
    //my monitor size :)
    m_view.reset(sf::FloatRect(0,0,1920*2,1080*2));
    m_view.zoom(0.8);
    m_rightHand.m_itemType = Ginfo::Entity::BLOCK;
    m_rightHand.m_itemID = 0;
    m_isInventoryOpen = false;

}

void CPlayer::tick()
{
    handleInput();
    pworld->CalculateNextPos(m_force, m_velocity, m_pos, sf::Vector2f(PLAYER_SIZE,PLAYER_SIZE));
    //set the view
    m_view.setCenter(sf::Vector2f(
    m_pos.x + (float)PLAYER_SIZE/2,
    m_pos.y + (float)PLAYER_SIZE/2));
}

void CWorld::setPlayer(CPlayer* pplayer)
{
    m_pPlayer = pplayer;
}

CPlayer* CWorld::player()const
{
    return m_pPlayer;
}
void CPlayer::handleInput()
{
    if (isKeyPressed(Input::PLAYER_INVENTORY) && !m_isInventoryOpen)
    {
        m_isInventoryOpen = true;
    }else if (isKeyPressed(Input::PLAYER_INVENTORY) && m_isInventoryOpen)
    {
        m_isInventoryOpen = false;
    }
    if (!m_isInventoryOpen)
    {
        if(isKeyDown(Input::A))m_force.x -= 3;
        if(isKeyDown(Input::D))m_force.x += 3;
        if(isKeyDown(Input::S))m_force.y += 3;
        if(isKeyDown(Input::W))m_force.y -= 3;
        if(isKeyDown(Input::ZOOM_IN))m_view.zoom(0.9);
        if(isKeyDown(Input::ZOOM_OUT))m_view.zoom(1.1);
        //block creation
        if (isKeyDown(Input::RMB))
        {
            pworld->createBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y,
            Ginfo::Block::Type(m_rightHand.m_itemID));
        }
        if (isKeyDown(Input::LMB))
        {
            pworld->distroyBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y);
        }
        //scroll through blocks
        if (isKeyPressed(Input::TOOLBAR_NEXT))
        {
            if (m_rightHand.m_itemID >= Ginfo::Block::TYPE_COUNT)
            {
                m_rightHand.m_itemID = 0;
            }else{
                ++m_rightHand.m_itemID;
            }
            // pgame->m_fps += 10;
        }
        if (isKeyPressed(Input::TOOLBAR_PREV))
        {
            if (m_rightHand.m_itemID <= Ginfo::Block::MIXED)
            {
                m_rightHand.m_itemID = Ginfo::Block::TYPE_COUNT-1;
            }else{
                --m_rightHand.m_itemID;
            }
            // pgame->m_fps -= 10;
        }
        if (isKeyDown(Input::REGEN_WORLD))
        {
            pworld->deleteTheWorld();
            pworld->generateWorld();
        }
    }
}
