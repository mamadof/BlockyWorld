#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "info.hpp"

class CDropItem{
    public:
    unsigned short m_count;
    bool m_merged;
    class CCell* m_pCell;
    Ginfo::Entity::Type m_type;
    long m_typeID;
    sf::Vector2f m_pos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_force;
    void tick(int order);
};

class CItemContainer{
    public:
    unsigned short m_count;
    bool m_merged;
    Ginfo::Entity::Type m_type;
    long m_typeID;
    sf::Vector2f m_pos;
    CItemContainer();
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
    unsigned m_rotation;//in radian
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
    unsigned m_rotation;//in radian
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
    sf::Vector2f m_force;//apply movement to the character
    unsigned m_HP;
    unsigned m_maxHP;
    bool m_grounded;//feet on the ground
    bool m_flying;
    bool m_rubbing;//is player rubbing against any surface ?
    bool m_isInventoryOpen;
    sf::Vector2f m_velocity;
    sf::View m_view;
    CPlayer();
    long m_holdingBlock;
    void tick();
    Hand_t m_leftHand;
    Hand_t m_rightHand;
    CItemContainer m_itemBar[PLAYER_ITEMBAR_SIZE];//player item bar you see in bottom
    CItemContainer m_inventory[PLAYER_INVENTORY_SIZE];//3row * 9col
    private:
    void handleInput();
};

class CCell{
    public:
    sf::Vector2f m_pos;
    CCell();
    CBlock m_BlockContent;
    void tick();
    bool m_tickNeeded;
    std::vector<CDropItem*> m_DropItems;//drop items in the cell
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
    unsigned long m_numberOfDropItems;
    sf::Vector2f m_groundFriction;
    sf::Vector2f m_airFriction;
    sf::RectangleShape m_border;
    CCell* getCellInArray(int x, int y);
    CCell* getCell(sf::Vector2f &pos);
    CCell* getCell(sf::Vector2f pos);
    CCell* getCell(int x, int y);
    CSmallBlock* getSmallBlock(int x, int y);
    CBlock* createBlock(int x, int y, Ginfo::Block::Type type, bool force = false);
    CSmallBlock* createSmallBlock(int x, int y, Ginfo::Block::Type type, bool force = false);
    bool distroyBlock(int x, int y);
    bool distroySmallBlock(int x, int y);
    //get pointer to player
    CPlayer* player()const;
    //don't use this
    void setPlayer(CPlayer* pplayer);
    //calculate all entities nex move
    void CalculateNextPos(
    sf::Vector2f &force,
    sf::Vector2f &velocity,
    sf::Vector2f &pos,
    sf::Vector2f size);

    void createDropItem(
    sf::Vector2f pos,
    Ginfo::Entity::Type type,
    long int type_ID = 0,//id of the type (in enum order)
    unsigned count = 1,
    sf::Vector2f velocity = sf::Vector2f(0,0));

    void generateWorld();
    void deleteTheWorld();

    private:
    CPlayer* m_pPlayer;
    /*position of every cell in the world*/
    CCell* ma_pCells;
};

class CMob{
    public:
    sf::Vector2f m_pos;
    sf::Vector2f m_force;//apply movement to the character
    unsigned m_HP;
    unsigned m_maxHP;
    bool m_grounded;//feet on the ground
    bool m_flying;
    bool m_rubbing;//is player rubbing against any surface ?
    sf::Vector2f m_velocity;
    sf::View m_view;
    CMob();
    long m_holdingBlock;
    void tick();
    Hand_t m_leftHand;
    Hand_t m_rightHand;
};

#endif //GAMEWORLD_HPP