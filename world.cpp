#include "gameWorld.hpp"
#include "share.hpp"
#include "math.hpp"
#include <math.h>

CWorld::CWorld(unsigned long width, unsigned long height)
{
    m_numberOfEntities = 0;
    m_numberOfBlocks = 0;
    m_numberOfSmallBlocks = 0;
    m_numberOfMobs = 0;
    m_numberOfItems = 0;
    m_groundFriction = DEFAULT_GROUND_FRICTION;
    m_airFriction = DEFAULT_AIR_FRICTION;
    m_width = width;
    m_height = height;
    //world border
    m_border.setSize(sf::Vector2f(width*GRID_SIZE, height*GRID_SIZE));
    m_border.setPosition(sf::Vector2f(0,0));
    m_border.setFillColor(sf::Color(0,255,100,60));
    m_border.setOutlineThickness(0);
    m_border.setOutlineColor(sf::Color(255,0,0,255));
    //world cells & blocks & small blocks
    ma_pCells = new CCell[width*height]();
    CCell* pCell;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            pCell = &ma_pCells[(x*height)+y];
            pCell->m_body.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
            pCell->m_body.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            pCell->m_body.setFillColor(sf::Color(0,255,50,80));
            pCell->m_BlockContent.m_deleted = true;
            pCell->m_BlockContent.m_body.
            setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
            pCell->m_BlockContent.m_body.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
            //iterate through small blocks (9*9 pieces)
            for (int x = 0; x < BLOCK_SUBDIVISION; x++)
            {
                for (int y = 0; y < BLOCK_SUBDIVISION; y++)
                {
                    pCell->m_BlockContent.
                    ma_SmallBlocks[x][y].m_deleted = true;

                    pCell->m_BlockContent.
                    ma_SmallBlocks[x][y].m_body.
                    setSize(sf::Vector2f((float)SMALL_BLOCK_SIZE,(float)SMALL_BLOCK_SIZE));

                    pCell->m_BlockContent.
                    ma_SmallBlocks[x][y].m_body.
                    setPosition(sf::Vector2f((float)x*SMALL_BLOCK_SIZE,(float)y*SMALL_BLOCK_SIZE));

                }
            }
        }
    }
}

void CWorld::tick()
{
    m_pPlayer->tick();
}

void CWorld::CalculateNextPos(sf::Vector2f &velocity, sf::RectangleShape &body)
{
    typedef sf::Vector2f v2f;
    CCell *pCell;
    v2f calpos = body.getPosition();//keep the player's position for calculation
    v2f calvel = velocity;//keep the player's velocity for calculation
    v2f recPoints[4] = {//four points of the rectangular body
        v2f(calpos.x, calpos.y),//top left point
        v2f(calpos.x + body.getSize().x, calpos.y),//top right point
        v2f(calpos.x, calpos.y  + body.getSize().y),//bottom left point
        v2f(calpos.x  + body.getSize().x, calpos.y  + body.getSize().y)//bottom right point
    };
    for (int i = 0; i < 4; i++)
    {
        pCell = getCell(recPoints[i] + calvel);
        if (pCell == NULL)continue;
        if(!pCell->m_BlockContent.m_deleted)
        {
            calvel.y = 0;
        }
        
        pCell = getCell(recPoints[i] + calvel);
        if (pCell == NULL)continue;
        if(!pCell->m_BlockContent.m_deleted)
        {
            calvel = velocity;//reset the velocity
            calvel.x = 0;
        }  
    }
    velocity = calvel;
    gm::v2v2scaleref(velocity, pworld->m_airFriction);
    body.setPosition(gm::v2add(body.getPosition(), velocity));
}
