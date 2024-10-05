#include "gameWorld.hpp"
#include "share.hpp"

CWorld::CWorld()
{
    m_numberOfEntities = 0;
    m_numberOfBlocks = 0;
    m_numberOfMobs = 0;
    m_numberOfItems = 0;
    m_blockFriction = 0.8;
    m_airFriction = 0.92;
    //init all blocks to NULL
    for (int x = 0; x < MAX_BLOCKS; x++)
    {
        for (int y = 0; y < MAX_BLOCKS; y++)
        {
            mpa_blocks[x][y] = NULL;
        }
    }
}

void CWorld::tick()
{
    mp_player->tick();
}

void CWorld::CalColVel(sf::Vector2f &pos, sf::Vector2f &velocity, sf::RectangleShape &body)
{
    typedef sf::Vector2f v2f;
    v2f recPoints[4] = {//four points of the rectangular body
        v2f(pos.x, pos.y),//top left point
        v2f(pos.x + body.getSize().x, pos.y),//top right point
        v2f(pos.x, pos.y  + body.getSize().y),//bottom left point
        v2f(pos.x  + body.getSize().x, pos.y  + body.getSize().y)//bottom right point
    };
    for (int i = 0; i < 4; i++)
    {
        if(BlockByPos(gm::v2add(recPoints[i], velocity)) != NULL)
        {
            velocity.y = 0;
        }
        if(BlockByPos(gm::v2add(recPoints[i], velocity)) != NULL)
        {
            velocity.x = 0;
        }
    }
    // printf("size of array:%d\n", );
}
