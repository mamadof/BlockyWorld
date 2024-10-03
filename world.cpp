#include "gameWorld.hpp"
#include "share.hpp"

void CWorld::tick()
{
    mp_player->tick();
    // for (int i = 0; i < m_numberOfEntities;i++)
    // {
    //     mpa_entities[i]->tick();
    // }
}

CWorld::CWorld()
{
    //init blocks to NULL
    for (int x = 0; x < MAX_BLOCKS; x++)
    {
        for (int y = 0; y < MAX_BLOCKS; y++)
        {
            mpa_blocks[x][y] = NULL;
        }
    }
    
}