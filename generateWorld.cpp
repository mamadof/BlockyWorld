#include "gameWorld.hpp"
#include <iostream>
#include <math.h>
#include <cstdlib>
void CWorld::generateWorld()
{
    srand(std::time(0));
    int grassHeight = m_height/3;
    for (int x = 0; x < m_width; ++x)
    {
        grassHeight += round(rand() / (RAND_MAX / 3))-1;
        createBlock(x * BLOCK_SIZE, grassHeight * BLOCK_SIZE, Ginfo::Block::GRASS);
        for (int y = grassHeight; y < m_height; ++y)
        {
            createBlock(x * BLOCK_SIZE, y * BLOCK_SIZE, Ginfo::Block::DIRT);
        }
    }
}

void CWorld::deleteTheWorld()
{
    for (int i = 0; i < m_height * m_width; i++)
    {
        ma_pCells[i].m_BlockContent.m_deleted = true;
        // distroyBlock(ma_pCells[i].m_BlockContent.m_pos.x, ma_pCells[i].m_BlockContent.m_pos.y);
        for (int x = 0; x < BLOCK_SUBDIVISION; x++)
        {
            for (int y = 0; y < BLOCK_SUBDIVISION; y++)
            {
                ma_pCells[i].m_BlockContent.ma_SmallBlocks[x][y].m_deleted = true;
            }
        }
    }
}