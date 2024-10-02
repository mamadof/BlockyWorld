#include "gameWorld.hpp"
#include "share.hpp"

void CWorld::tick()
{

}

void CEntity::tick()
{

}

CWorld::CWorld()
{
    
}

CPlayer* CWorld::player()
{

}

CPlayer::CPlayer()
{
    m_x = 50;
    m_y = 50;
    m_body.setPosition(m_x, m_y);
    m_body.setFillColor(sf::Color::Black);
    m_body.setSize(sf::Vector2f(50,100));
    m_shown = true;
    m_movable = true;
    m_ghost = false;
    m_HP = 50;
    m_maxHP = 50;
    m_ID = pworld->m_numberOfEntities;
    ++pworld->m_numberOfEntities;
}

CBlock* CWorld::blockByArray(int x, int y)
{

}

CBlock* CWorld::BlockByPos(int x, int y)
{

}

CBlock* CWorld::createBlock(int x, int y)
{

}