#include "gameWorld.hpp"
#include "share.hpp"
#include <limits.h>
#include "math.hpp"

CItemContainer::CItemContainer()
{
    m_count = 0;
    m_merged = false;
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
    pDropItem->m_force = sf::Vector2f(0,0);
    pDropItem->m_count = count;
    pDropItem->m_pos = pos;
    pDropItem->m_pCell = pcell;
    pDropItem->m_velocity = sf::Vector2f(0,0);
    pcell->m_DropItems.push_back(pDropItem);
    ++pworld->m_numberOfDropItems;
}

void CDropItem::tick(int order)
{
    CPlayer* pPlayer = pworld->player();
    if (gm::v2distance(m_pCell->m_pos, pPlayer->m_pos) <= ITEM_DROP_PICKUP_RANGE)
    {
        for (int i = 0; i < PLAYER_INVENTORY_SIZE; i++)
        {
            if (pPlayer->m_inventory[i].m_count >= ITEM_CONTAINER_STACK_SIZE ||
                pPlayer->m_inventory[i].m_count + m_count >= ITEM_CONTAINER_STACK_SIZE)continue;

            if (pPlayer->m_inventory[i].m_count > 0 &&
                (pPlayer->m_inventory[i].m_type != m_type ||
                pPlayer->m_inventory[i].m_typeID != m_typeID))continue;

            CDropItem *pDrop = m_pCell->m_DropItems.at(order);
            m_pCell->m_DropItems.erase(m_pCell->m_DropItems.begin() + order);
            --pworld->m_numberOfDropItems;
            pPlayer->m_inventory[i].m_count += m_count;
            pPlayer->m_inventory[i].m_type = m_type;
            pPlayer->m_inventory[i].m_typeID = m_typeID;
            delete pDrop;
            return;
        }
    }

    if (gm::v2distance(m_pCell->m_pos, pPlayer->m_pos) <= ITEM_DROP_PLAYER_MAGNET)
    {
        m_force += gm::v2ForceTowards(m_pos, pPlayer->m_pos, 2);
    }

    pworld->CalculateNextPos(m_force, m_velocity, m_pos, sf::Vector2f(DROP_ITEM_SIZE,DROP_ITEM_SIZE));
    CCell* pCell = pworld->getCell(sf::Vector2f(m_pos));
    //if drop item goes beyond world borders it will get deleted :)
    if (m_pCell->m_DropItems.at(order)->m_pos.y > (pworld->m_height + 10) * CELL_SIZE)
    {
        CDropItem *pDrop = m_pCell->m_DropItems.at(order);
        m_pCell->m_DropItems.erase(m_pCell->m_DropItems.begin() + order);
        --pworld->m_numberOfDropItems;
        delete pDrop;
        return;
    }
    //merge them :)
    if (order > 0 &&
    m_pCell->m_DropItems.at(order)->m_type == m_pCell->m_DropItems.at(order-1)->m_type &&
    m_pCell->m_DropItems.at(order)->m_typeID == m_pCell->m_DropItems.at(order-1)->m_typeID &&
    m_pCell->m_DropItems.at(order-1)->m_count < USHRT_MAX)
    {
        m_pCell->m_DropItems.at(order-1)->m_count += m_pCell->m_DropItems.at(order)->m_count + 1;
        CDropItem *pDrop = m_pCell->m_DropItems.at(order);
        m_pCell->m_DropItems.erase(m_pCell->m_DropItems.begin() + order);
        --pworld->m_numberOfDropItems;
        delete pDrop;
        return;
    }
    //change the cell when they move :)
    if (pCell != NULL && m_pCell != pCell)
    {
        m_pCell->m_DropItems.erase(m_pCell->m_DropItems.begin() + order);
        m_pCell = pCell;
        m_pCell->m_DropItems.push_back(this);
    }

}   
