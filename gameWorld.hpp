#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "share.hpp"
#include "info.hpp"

class CDropItem{
    public:
    unsigned m_count;
    bool m_merged;
    Ginfo::Entity::Type m_type;
    long m_typeID;
    sf::Vector2f m_pos;
    sf::Vector2f m_velocity;
    void tick();
};

/*small blocks ingredients:
electron, neutron, proton*/
typedef struct{
    unsigned m_e;
    unsigned m_n;
    unsigned m_p;
}Particles;

class CSmallBlock{
    public:
    sf::Vector2f m_pos;
    bool m_deleted;
    CSmallBlock();
    Ginfo::Block::Type m_type;//small blocks can't have mixed type
    Particles m_particles;
    unsigned m_HP;
    unsigned m_maxHP;
    void tick();
    private:
};

class CBlock{
    public:
    sf::Vector2f m_pos;
    bool m_deleted;
    Ginfo::Block::Type m_type;
    CSmallBlock ma_SmallBlocks[BLOCK_SUBDIVISION][BLOCK_SUBDIVISION];
    unsigned m_HP;
    unsigned m_maxHP;
    void tick();
    private:
};

typedef struct{
    Ginfo::Entity::Type m_itemType;
    int m_itemID;
    int m_itemcount;
    unsigned m_handSpeed;
}Hand_t;

class CPlayer{
    public:
    sf::Vector2f m_pos;
    unsigned m_HP;
    unsigned m_maxHP;
    bool m_grounded;//feet on the ground
    bool m_flying;
    bool m_rubbing;//is player rubbing against any surface ?
    sf::Vector2f m_velocity;//velocity that programmer control for further movement controll
    sf::View m_view;
    CPlayer();
    long m_holdingBlock;
    void tick();
    Hand_t m_leftHand;
    Hand_t m_rightHand;
};

class CCell{
    public:
    sf::Vector2f m_pos;
    CCell();
    CBlock m_BlockContent;
    void tick();
    bool m_tickNeeded;
    bool m_ticked;
    std::vector<CDropItem> m_DropItems;//drop items in the cell
    private:
};

class CWorld{
    private:
    
    public:
    CWorld(unsigned long width, unsigned long height);
    void tick();
    unsigned long m_width;//world width
    unsigned long m_height;//world height
    unsigned long m_numberOfEntities;
    unsigned long m_numberOfBlocks;
    unsigned long m_numberOfSmallBlocks;
    unsigned long m_numberOfMobs;
    unsigned long m_numberOfItems;
    sf::Vector2f m_groundFriction;
    sf::Vector2f m_airFriction;
    sf::RectangleShape m_border;
    CCell* getCellInArray(int x, int y);
    CCell* getCell(sf::Vector2f &pos);
    CCell* getCell(sf::Vector2f pos);
    CCell* getCell(int x, int y);
    CBlock* createBlock(int x, int y, Ginfo::Block::Type type, bool force = false);
    CSmallBlock* createSmallBlock(int x, int y, Ginfo::Block::Type type, bool force = false);
    bool distroyBlock(int x, int y);
    bool distroySmallBlock(int x, int y);
    //get pointer to player
    CPlayer* player()const;
    //don't use this
    void setPlayer(CPlayer* pplayer);
    //calculate player's next move
    void CalculateNextPos(
    sf::Vector2f &velocity,
    sf::Vector2f &pos,
    Ginfo::Entity::Type type);

    void createDropItem(
    sf::Vector2f pos,
    Ginfo::Entity::Type type,
    long int type_ID = 0,
    unsigned count = 1,
    sf::Vector2f velocity = sf::Vector2f(0,0));

    private:
    CPlayer* m_pPlayer;
    /*position of every cell in the world*/
    CCell* ma_pCells;
};

#endif //GAMEWORLD_HPP