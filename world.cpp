#include <map>
#include <vector>
#include "share.hpp"
#include "gameWorld.hpp"
#include "math.hpp"
#include <math.h>
#include <limits.h>

CWorld::CWorld(unsigned long width, unsigned long height)
{
    m_numberOfEntities = 0;
    m_numberOfBlocks = 0;
    m_numberOfSmallBlocks = 0;
    m_numberOfMobs = 0;
    m_numberOfItems = 0;
    m_numberOfDropItems = 0;
    m_groundFriction = DEFAULT_GROUND_FRICTION;
    m_airFriction = DEFAULT_AIR_FRICTION;
    m_width = width;
    m_height = height;
    //world border
    m_border.setSize(sf::Vector2f(width*GRID_SIZE, height*GRID_SIZE));
    m_border.setPosition(sf::Vector2f(0,0));
    m_border.setFillColor(sf::Color(120,120,255,255));
    //world cells & blocks & small blocks
    ma_pCells = new CCell[width*height]();
    CCell* pCell;
    CBlock* pBlock;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            pCell = &ma_pCells[(x*height)+y];
            pBlock = &pCell->m_BlockContent;
            pCell->m_tickNeeded = true;
            pBlock->m_deleted = true;
            pCell->m_pos = sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            pBlock->m_pos = sf::Vector2f(x * BLOCK_SIZE, y * BLOCK_SIZE);
            //iterate through small blocks (9*9 pieces)
            CSmallBlock* pSmallBlock;
            for (int x = 0; x < BLOCK_SUBDIVISION; x++)
            {
                for (int y = 0; y < BLOCK_SUBDIVISION; y++)
                {
                    pSmallBlock = &pBlock->ma_SmallBlocks[x][y];
                    pSmallBlock->m_deleted = true;

                    pSmallBlock->m_pos.x = x * SMALL_BLOCK_SIZE + pBlock->m_pos.x;
                    pSmallBlock->m_pos.y = y * SMALL_BLOCK_SIZE + pBlock->m_pos.y;

                }
            }
        }
    }
}

void CWorld::tick()
{
    m_pPlayer->tick();
    //tick all the cells
    for (int i = 0; i < m_width*m_height; i++)
    {
        if (ma_pCells[i].m_tickNeeded)
        {
            ma_pCells[i].tick();
        }
    }
}

void CWorld::CalculateNextPos(
sf::Vector2f &force,
sf::Vector2f &velocity,
sf::Vector2f &pos,
sf::Vector2f size)
{
    typedef sf::Vector2f v2f;
    v2f rectPoints[4] = {//four points of the rectangular body
        v2f(pos.x, pos.y),//top left point
        v2f(pos.x + size.x, pos.y),//top right point
        v2f(pos.x, pos.y  + size.y),//bottom left point
        v2f(pos.x  + size.x, pos.y  + size.y)//bottom right point
    };
    CCell *pCell;
    v2f nextPos;
    nextPos = force;
    nextPos += DEFAULT_GRAVITY;
    nextPos += velocity;
    nextPos -= gm::v2v2scale(nextPos, DEFAULT_AIR_FRICTION);
    v2f nextPos2 = nextPos;
    v2f prePos = pos;


    for (int i = 0; i < 4; i++)
    {
        pCell = getCell(rectPoints[i] + nextPos);
        if (pCell == NULL)continue;
        if(!pCell->m_BlockContent.m_deleted)
        {
            nextPos.y = 0;
        }
        
        pCell = getCell(rectPoints[i] + nextPos);
        if (pCell == NULL)continue;
        if(!pCell->m_BlockContent.m_deleted)
        {
            nextPos = nextPos2;
            nextPos.x = 0;
        }  
    }
    // gm::v2v2scaleref(force2, pworld->m_airFriction);
    // gm::v2addref(pos, nextPos);
    pos = pos + nextPos;
    force = v2f(0,0);
    velocity = (pos - prePos);
    // printf("%f\n", gm::v2distance(v2f(0,0), velocity));
}

void CCell::tick()
{
    //tick all the blocks
    if (!m_BlockContent.m_deleted)
    {
        m_BlockContent.tick();
    }
    //tick all drop items
    if(m_DropItems.size() > 0)
    {
        for (int i = 0; i < m_DropItems.size(); i++)
        {
            m_DropItems.at(i)->tick(i);
        }
    }
}

