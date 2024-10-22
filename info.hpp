#ifndef INFO_HPP
#define INFO_HPP
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

// #define DEFAULT_FPS 60

#define GRID_SIZE 81
#define CELL_SIZE 81
#define BLOCK_SIZE 81
#define BLOCK_SUBDIVISION 9//number of small blocks in a single block
#define SMALL_BLOCK_SIZE 9

#define PLAYER_SIZE 75
#define PLAYER_SPRITE_SIZE 81//the drawable sprite
#define PLAYER_ITEMBAR_SIZE 9
#define PLAYER_INVENTORY_SIZE 27

#define DEFAULT_AIR_FRICTION sf::Vector2f(0.06, 0)
#define DEFAULT_GROUND_FRICTION sf::Vector2f(0.96, 0.99)
#define DEFAULT_GRAVITY sf::Vector2f(0, 1)

#define DROP_ITEM_SIZE 39
#define ITEM_DROP_PICKUP_RANGE 75
#define ITEM_DROP_PLAYER_MAGNET 250
#define ITEM_DROP_STACK_SIZE 120

#define ITEM_CONTAINER_SIZE 50//those rectangles you see in chests and players inventory
#define ITEM_CONTAINER_SPRITE_SIZE 45
#define ITEM_CONTAINER_STACK_SIZE 120

namespace Ginfo{//stands for game info
    namespace Entity
    {
        typedef enum{
            BLOCK,
            SMALL_BLOCK,
            PLAYER,
            MOB,
            ITEM,
            DROP_ITEM,
            PARTICLE,
            TYPE_COUNT
        }Type;
    }
    
    namespace Block
    {
        typedef enum{
            MIXED,
            DIRT,
            GRASS,
            STONE,
            WOOD,
            LEAF,
            GLASS,
            IRON_ORE,
            COPPER_ORE,
            GOLD_ORE,
            TITANITE_ORE,
            ENEMY_SPAWN,
            CONVEYOR,
            TYPE_COUNT
        }Type;

        typedef enum{
            MAXHP,
            SPRITE_X,
            SPRITE_Y,
            INFO_COUNT
        }Info;
    }  

    namespace player
    {
        typedef enum{
            GROUND_NOT_MOVING,
            GROUND_RUNNING_0,
            GROUND_RUNNING_1,
            GROUND_RUNNING_2,
            FLYING_NOT_MOVING,
            FLYING_0,
            FLYING_1,
            FLYING_2,
            FRAME_COUNT
        }Frame;
    }

    namespace Texture
    {
        enum{
            BLOCK_TEXTURE,
            PLAYER_TEXTURE,
            TEXTURE_COUNT
        };
    }
}
void loadInfos();

unsigned long& getBlockMaxHP(Ginfo::Block::Type type);
struct particle& getBlockParticle(Ginfo::Block::Type type);

#endif //INFO_HPP