#include "share.hpp"
#include "gameWorld.hpp"
#include "game.hpp"
#include "math.hpp"

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
    this->m_body.setSize(sf::Vector2f((float)SMALL_BLOCK_SIZE,(float)SMALL_BLOCK_SIZE));
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

CBlock* CWorld::createBlock(int x, int y, Block_Type type, bool force)
{
    //check the cell
    CCell* pCell = getCell(x,y);
    if (pCell == NULL)return NULL;
    if (!pCell->m_BlockContent.m_deleted)return NULL;
    CBlock* pBlock = &pCell->m_BlockContent;
    pBlock->m_deleted = false;
    pBlock->m_type = type;
    //allocate memory for small blocks
    if (type != gt::block::MIXED)
    {
        for (int x = 0; x < BLOCK_SUBDIVISION; x++)
        {
            for (int y = 0; y < BLOCK_SUBDIVISION; y++)
            {
                pBlock->ma_SmallBlocks[x][y].m_deleted = false;
                pBlock->ma_SmallBlocks[x][y].m_type = type;
                pBlock->ma_SmallBlocks[x][y].m_body.
                setPosition(sf::Vector2f(
                pBlock->m_body.getPosition().x + ((float)x*SMALL_BLOCK_SIZE),
                pBlock->m_body.getPosition().y + ((float)y*SMALL_BLOCK_SIZE)));
            }
        }
    }
    return pBlock;
}

CSmallBlock* CWorld::createSmallBlock(int x, int y, Block_Type type, bool force)
{

}

bool CWorld::distroyBlock(int x, int y)
{
    CCell* pCell = getCell(x,y);
    if (pCell == NULL)return false;
    if (pCell->m_BlockContent.m_deleted)return false;
    CBlock* pBlock = &pCell->m_BlockContent;
    pBlock->m_deleted = true;
    for (int x = 0; x < BLOCK_SUBDIVISION; x++)
    {
        for (int y = 0; y < BLOCK_SUBDIVISION; y++)
        {
            pBlock->ma_SmallBlocks[x][y].m_deleted = true;
        }
    }
    return true;
}

bool CWorld::distroySmallBlock(int x, int y)
{

}