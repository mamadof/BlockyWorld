#include "share.hpp"

CBlock::CBlock(int x, int y, bool ghost)
{
    m_body.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE));
    // m_body.setFillColor(sf::Color::);
    m_body.setPosition(x, y);
    m_x = x;
    m_y = y;
    m_ghost = ghost;
}


bool CWorld::distroyBlock(int x, int y)
{
    if (x > (MAX_BLOCKS*GRID_SIZE)-1 || y > (MAX_BLOCKS*GRID_SIZE)-1
    || x < 0 || y < 0)return false;
    CBlock* pblock = BlockByPos(x, y);
    if (pblock == NULL)return false;
    delete pblock;
    pworld->mpa_blocks[x/GRID_SIZE][y/GRID_SIZE] = NULL;
    return true;
}

CBlock* CWorld::createBlock(int x, int y, bool ghost)
{
    if (BlockByPos(x, y) != NULL)return NULL;
    if (x > (MAX_BLOCKS*GRID_SIZE)-1 || y > (MAX_BLOCKS*GRID_SIZE)-1
    || x < 0 || y < 0)return NULL;
    CBlock* pblock = new CBlock(snapToGrid(x,y).x, snapToGrid(x,y).y);
    pworld->mpa_blocks[x/GRID_SIZE][y/GRID_SIZE] = pblock;
    return pblock;
}

CBlock* CWorld::blockByArray(int x, int y)
{
    if (x > MAX_BLOCKS || x < 0 || y > MAX_BLOCKS || y < 0)return NULL;
    CBlock* pblock = mpa_blocks[x][y];
    return pblock;
}

CBlock* CWorld::BlockByPos(int x, int y)
{
    if (x > (MAX_BLOCKS*GRID_SIZE)-1 || x < 0 || y > (MAX_BLOCKS*GRID_SIZE)-1 || y < 0)return NULL;
    CBlock* pblock = blockByArray(x/GRID_SIZE,y/GRID_SIZE);
    return pblock;
}