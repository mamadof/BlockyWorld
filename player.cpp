#include "share.hpp"

CPlayer::CPlayer()
{
    m_x = 50;
    m_y = 50;
    m_body.setPosition(m_x, m_y);
    m_body.setFillColor(sf::Color::Black);
    m_body.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE*2));
    m_body.setOrigin(sf::Vector2f(static_cast<int>(GRID_SIZE/2), GRID_SIZE));
    m_shown = true;
    m_movable = true;
    m_ghost = false;
    m_HP = 50;
    m_maxHP = 50;
    m_view.reset(sf::FloatRect(0,0,1920,1080));
    m_view.setCenter(sf::Vector2f(m_x,m_y));
}

void CPlayer::tick()
{
    //movement
    if(Input::getGameKeyState(Input::A))m_x -= 20;
    if(Input::getGameKeyState(Input::D))m_x += 20;
    if(Input::getGameKeyState(Input::S))m_y += 20;
    if(Input::getGameKeyState(Input::W))m_y -= 20;
    //block creation
    if(Input::getGameKeyState(Input::RMB))
    {
        pworld->createBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y);
    }
    if(Input::getGameKeyState(Input::LMB))
    {
        pworld->distroyBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y);
    }
    

    m_body.setPosition(sf::Vector2f(m_x ,m_y));
    m_view.setCenter(sf::Vector2f(m_x, m_y));
}

void CWorld::setPlayer(CPlayer* pplayer)
{
    mp_player = pplayer;
}

CPlayer* CWorld::player()
{
    return mp_player;
}