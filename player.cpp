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
    //my monitor size :)
    m_view.reset(sf::FloatRect(0,0,1920*2,1080*2));
}

void CPlayer::tick()
{
    //movement to the velocity
    if(Input::getGameKeyState(Input::A))m_velocity.x -= 3;
    if(Input::getGameKeyState(Input::D))m_velocity.x += 3;
    if(Input::getGameKeyState(Input::S))m_velocity.y += 3;
    if(Input::getGameKeyState(Input::W))m_velocity.y -= 3;
    if(Input::getGameKeyState(Input::ZOOM_IN))m_view.zoom(0.9);
    if(Input::getGameKeyState(Input::ZOOM_OUT))m_view.zoom(1.1);
    m_velocity.y += 1;
    //important: call collision and then set the positions
    pworld->CalculateNextPos(m_velocity, m_pos, Ginfo::Entity::PLAYER);
    //set the view
    m_view.setCenter(sf::Vector2f(
    m_pos.x + (float)PLAYER_SIZE/2,
    m_pos.y + (float)PLAYER_SIZE/2));
    //block creation
    if(Input::getGameKeyState(Input::RMB))
    {
        pworld->createBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y, Ginfo::Block::GLASS);
    }
    if(Input::getGameKeyState(Input::LMB))
    {
        pworld->distroyBlock(pgame->m_mousePosWorld.x, pgame->m_mousePosWorld.y);
    }
}

void CWorld::setPlayer(CPlayer* pplayer)
{
    m_pPlayer = pplayer;
}

CPlayer* CWorld::player()const
{
    return m_pPlayer;
}