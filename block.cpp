#include "share.hpp"
#include "gameWorld.hpp"
#include "game.hpp"
#include "math.hpp"
#include <cstdlib>

CCell* CWorld::getCellInArray(int x, int y)
{
    //i don't know why -1 but it fixes the fucking bug
    if(x > m_width-1)return NULL;
    if(y > m_height-1)return NULL;
    if(x < 0)return NULL;
    if(y < 0)return NULL;

    return &ma_pCells[(x*m_height)+y];

}
CSmallBlock::CSmallBlock()
{

}
CCell::CCell()
{
    
}
CCell* CWorld::getCell(int x, int y)
{
    return getCellInArray((int)x/CELL_SIZE, (int)y/CELL_SIZE);
}
CCell* CWorld::getCell(sf::Vector2f &pos)
{
    return getCell((int)pos.x, (int)pos.y);
}
CCell* CWorld::getCell(sf::Vector2f pos)
{
    return getCell((int)pos.x, (int)pos.y);
}

CBlock* CWorld::createBlock(int x, int y, Ginfo::Block::Type type, bool force)
{
    //check the cell
    CCell* pCell = getCell(x,y);
    if (pCell == NULL)return NULL;
    if (!pCell->m_BlockContent.m_deleted)return NULL;
    CBlock* pBlock = &pCell->m_BlockContent;
    pBlock->m_deleted = false;
    pBlock->m_type = type;
    //allocate memory for small blocks
    if (type != Ginfo::Block::MIXED)
    {
        for (int x = 0; x < BLOCK_SUBDIVISION; x++)
        {
            for (int y = 0; y < BLOCK_SUBDIVISION; y++)
            {
                pBlock->ma_SmallBlocks[x][y].m_deleted = false;
                pBlock->ma_SmallBlocks[x][y].m_type = type;
                pBlock->ma_SmallBlocks[x][y].m_pos =
                sf::Vector2f(
                pBlock->m_pos.x + ((float)x*SMALL_BLOCK_SIZE),
                pBlock->m_pos.y + ((float)y*SMALL_BLOCK_SIZE));
            }
        }
    }
    return pBlock;
}

CSmallBlock* CWorld::createSmallBlock(int x, int y, Ginfo::Block::Type type, bool force)
{

}

bool CWorld::distroyBlock(int x, int y)
{
    long type;
    sf::Vector2f dropPos;
    CCell* pCell = getCell(x,y);
    if (pCell == NULL)return false;
    if (pCell->m_BlockContent.m_deleted)return false;
    CBlock* pBlock = &pCell->m_BlockContent;
    type = pBlock->m_type;
    dropPos = pBlock->m_pos;
    pBlock->m_deleted = true;
    for (int x = 0; x < BLOCK_SUBDIVISION; x++)
    {
        for (int y = 0; y < BLOCK_SUBDIVISION; y++)
        {
            pBlock->ma_SmallBlocks[x][y].m_deleted = true;
        }
    }
    createDropItem(
    sf::Vector2f(dropPos.x + (float)rand()/((float)RAND_MAX/80),dropPos.y + (float)rand()/((float)RAND_MAX/80)),
    Ginfo::Entity::BLOCK,
    type);
    return true;
}

bool CWorld::distroySmallBlock(int x, int y)
{

}