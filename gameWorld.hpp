#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP
#include <SFML/Graphics.hpp>

enum EntityType{
    BLOCK,
    PLAYER,
    MOB,
    ITEM,
    TYPE_COUNT
};

#define MAX_ENTITIES 1000
#define MAX_BLOCKS 100

class CWorld{
    public:
    CWorld();
    void tick();
    unsigned long m_numberOfEntities = 0;
    unsigned long m_numberOfBlocks = 0;
    unsigned long m_numberOfMobs = 0;
    unsigned long m_numberOfItems = 0;
    class CPlayer* player();//get the player pointer
    class CBlock* blockByArray(int x, int y);//block in the array
    class CBlock* BlockByPos(int x, int y);//block in the cordinate
    class CBlock* createBlock(int x, int y, bool ghost = false);//create block on that cordinate
    bool distroyBlock(int x, int y);//create block on that cordinate
    void setPlayer(CPlayer* pplayer);

    private:
    unsigned long m_width;
    unsigned long m_height;
    class CPlayer* mp_player;
    class CEntity* mpa_mobs[MAX_ENTITIES];
    class CEntity* mpa_items[MAX_ENTITIES];
    class CBlock* mpa_blocks[MAX_BLOCKS][MAX_BLOCKS];
    
};

class CEntity{
    public:
    long m_x;
    long m_y;
    bool m_shown;
    bool m_ghost;
    bool m_movable;
    unsigned long m_ID;
    CEntity();
    void tick();
};

class CPlayer : public CEntity{
    public:
    unsigned m_HP;
    unsigned m_maxHP;
    sf::View m_view;
    sf::RectangleShape m_body;

    CPlayer();
    void tick();
};

class CBlock : public CEntity{
    public:
    enum Type{
        GRASS,
        STONE,
        GLASS,
        TYPE_COUNT
    };
    CBlock(int x, int y, bool ghost = false);
    unsigned m_HP;
    unsigned m_maxHP;
    sf::RectangleShape m_body;
    void tick();
    private:
};

#endif //GAMEWORLD_HPP