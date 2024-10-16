#include <map>
#include <vector>
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
            pCell->m_BlockContent.m_deleted = true;
            pCell->m_pos = sf::Vector2f(x * BLOCK_SIZE, y * BLOCK_SIZE);
            pCell->m_BlockContent.m_pos = sf::Vector2f(x * BLOCK_SIZE, y * BLOCK_SIZE);
            //iterate through small blocks (9*9 pieces)
            for (int x = 0; x < BLOCK_SUBDIVISION; x++)
            {
                for (int y = 0; y < BLOCK_SUBDIVISION; y++)
                {
                    pCell->m_BlockContent.
                    ma_SmallBlocks[x][y].m_deleted = true;

                    pCell->m_BlockContent.
                    ma_SmallBlocks[x][y].m_pos =
                    sf::Vector2f((float)x*SMALL_BLOCK_SIZE,(float)y*SMALL_BLOCK_SIZE);

                }
            }
        }
    }
}

void CWorld::tick()
{
    m_pPlayer->tick();
}

void CWorld::CalculateNextPos(
sf::Vector2f &velocity,
sf::Vector2f &pos,
Ginfo::Entity::Type type)
{
    typedef sf::Vector2f v2f;
    CCell *pCell;
    v2f calpos = pos;//keep the player's position for calculation
    v2f calvel = velocity;//keep the player's velocity for calculation
    v2f recPoints[4] = {//four points of the rectangular body
        v2f(calpos.x, calpos.y),//top left point
        v2f(calpos.x + PLAYER_SIZE, calpos.y),//top right point
        v2f(calpos.x, calpos.y  + PLAYER_SIZE),//bottom left point
        v2f(calpos.x  + PLAYER_SIZE, calpos.y  + PLAYER_SIZE)//bottom right point
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
    gm::v2addref(pos, calvel);
}

void CWorld::createDropItem(
    sf::Vector2f pos,
    Ginfo::Entity::Type type,
    long typeID,
    unsigned count,
    sf::Vector2f velocity)
{
    CCell *pcell = getCell(pos.x,pos.y);
    if (pcell == NULL)return;

    CDropItem *pDropItem = new CDropItem;
    pDropItem->m_type = type;
    pDropItem->m_typeID = typeID;
    pDropItem->m_count = count;
    pDropItem->m_pos = pos;
    pcell->m_DropItems.push_back(*pDropItem);
}
