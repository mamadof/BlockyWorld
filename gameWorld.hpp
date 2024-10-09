#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP
#include <SFML/Graphics.hpp>
#include "share.hpp"

using gt::block::Block_Type;

/*small blocks ingredients:
electron, neutron, proton*/
typedef struct{
    unsigned m_e;
    unsigned m_n;
    unsigned m_p;
}Particles;

class CEntity{
    public:
    unsigned long m_UID;//unique ID
    sf::RectangleShape m_body;
};

class CSmallBlock : public CEntity{
    public:
    bool m_deleted;
    CSmallBlock();
    gt::block::Block_Type m_type;//small blocks can't have mixed type
    Particles m_particles;
    unsigned m_HP;
    unsigned m_maxHP;
    void tick();
    private:
};

class CBlock : public CEntity{
    public:
    bool m_deleted;
    Block_Type m_type;
    CSmallBlock ma_SmallBlocks[BLOCK_SUBDIVISION][BLOCK_SUBDIVISION];
    unsigned m_HP;
    unsigned m_maxHP;
    void tick();
    private:
};

class CPlayer : public CEntity{
    public:
    unsigned m_HP;
    unsigned m_maxHP;
    bool m_grounded;//feet on the ground
    bool m_flying;
    bool m_rubbing;//is player rubbing against any surface ?
    sf::Vector2f m_velocity;//velocity that programmer control for further movement controll
    sf::View m_view;
    CPlayer();
    void tick();
};

class CCell{

    public:
    CCell();
    sf::RectangleShape m_body;//rectangular body
    CBlock m_BlockContent;
    void tick();
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
    CBlock* createBlock(int x, int y, Block_Type type, bool force = false);
    CSmallBlock* createSmallBlock(int x, int y, Block_Type type, bool force = false);
    bool distroyBlock(int x, int y);
    bool distroySmallBlock(int x, int y);
    //get pointer to player
    CPlayer* player()const;
    //don't use this
    void setPlayer(CPlayer* pplayer);
    //calculate player's next move
    void CalculateNextPos(sf::Vector2f &velocity, sf::RectangleShape &body);

    private:
    CPlayer* m_pPlayer;
    /*position of every cell in the world*/
    CCell* ma_pCells;
};

#endif //GAMEWORLD_HPP