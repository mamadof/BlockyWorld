#ifndef SHARE_HPP
#define SHARE_HPP
//standar libraries
#include <SFML/Graphics.hpp>

extern sf::RenderWindow sf_window;
extern sf::Event sf_event;
extern class CGame *pgame;
extern class CWorld *pworld;

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define CELL_SIZE 81
#define BLOCK_SIZE CELL_SIZE
#define BLOCK_SUBDIVISION 9//number of small blocks in a single block
#define SMALL_BLOCK_SIZE BLOCK_SIZE/BLOCK_SUBDIVISION
#define GRID_SIZE CELL_SIZE
#define PLAYER_SIZE 75//player and mob size
#define PLAYER_SPRITE_SIZE 81//the drawable sprite
#define DEFAULT_AIR_FRICTION sf::Vector2f(0.93, 1)
#define DEFAULT_GROUND_FRICTION sf::Vector2f(0.96, 0.99)
#define DEFAULT_FPS 60

namespace gt{//stands for game types
    namespace entity
    {
        typedef enum{
        BLOCK,
        SMALL_BLOCK,
        PLAYER,
        MOB,
        ITEM,
        TYPE_COUNT
        }Entity_Type;
    }
    
    namespace block
    {
        typedef enum{
        DIRT,
        GRASS,
        STONE,
        GLASS,
        MIXED,
        TYPE_COUNT
        }Block_Type;
    }  
}

#endif //SHARE_HPP
