#ifndef INFO_HPP
#define INFO_HPP
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define CELL_SIZE 81
#define BLOCK_SIZE CELL_SIZE
#define BLOCK_SUBDIVISION 9//number of small blocks in a single block
#define SMALL_BLOCK_SIZE BLOCK_SIZE/BLOCK_SUBDIVISION
#define GRID_SIZE CELL_SIZE
#define PLAYER_SIZE 75//player and mob size
#define PLAYER_SPRITE_SIZE 81//the drawable sprite
#define DROP_ITEM_SIZE 21
#define DEFAULT_AIR_FRICTION sf::Vector2f(0.93, 1)
#define DEFAULT_GROUND_FRICTION sf::Vector2f(0.96, 0.99)
#define DEFAULT_FPS 60

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
            GLASS,
            IRON,
            COPPER,
            WOOD,
            LEAF,
            MILF,
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
            STAND,
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