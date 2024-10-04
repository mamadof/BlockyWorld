#include "share.hpp"

CPlayer::CPlayer()
{
    m_pos = sf::Vector2f(0,0);
    m_body.setPosition(m_pos);
    m_body.setFillColor(sf::Color::Black);
    m_body.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE*2));
    m_shown = true;
    m_movable = true;
    m_ghost = false;
    m_HP = 50;
    m_maxHP = 50;
    m_view.reset(sf::FloatRect(0,0,1920,1080));
    m_view.setCenter(m_pos);
}

void CPlayer::tick()
{
    //movement to the velocity
    if(Input::getGameKeyState(Input::A))m_velocity.x -= 3;
    if(Input::getGameKeyState(Input::D))m_velocity.x += 3;
    if(Input::getGameKeyState(Input::S))m_velocity.y += 3;
    if(Input::getGameKeyState(Input::W))m_velocity.y -= 3;
    m_velocity.y += 1;
    //important: call collision and then set the positions
    pworld->CalColVel(m_pos, m_velocity, m_body);
    //add frictios
    gm::v2scaleref(m_velocity, pworld->m_airFriction);
    //add velocity to the pos
    gm::v2addref(m_pos, m_velocity);
    m_body.setPosition(m_pos);
    m_view.setCenter(m_pos);
    
    //block creation
    if(Input::getGameKeyState(Input::RMB))
    {
        pworld->createBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y);
    }
    if(Input::getGameKeyState(Input::LMB))
    {
        pworld->distroyBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y);
    }
    m_preVelocity = m_velocity;
}

void CWorld::setPlayer(CPlayer* pplayer)
{
    mp_player = pplayer;
}

CPlayer* CWorld::player()
{
    return mp_player;
}