#include <SFML/Graphics.hpp>
#include "info.hpp"
#include <math.h>

using namespace std;
namespace gm{ //stands for game math
    inline float v2distance(sf::Vector2f v1, sf::Vector2f v2)
    {
        //d=√((x2 – x1)² + (y2 – y1)²)
        return sqrt(pow(v2.x - v1.x,2) + pow(v2.y - v1.y,2));
    }

    inline void v2addref(sf::Vector2f &v1, sf::Vector2f &v2)
    {
        v1.x += v2.x;
        v1.y += v2.y;
    }
    inline sf::Vector2f v2add(sf::Vector2f const &v1, sf::Vector2f const &v2)
    {
        return sf::Vector2f(v1.x + v2.x, v1.y + v2.y);
    }

    inline sf::Vector2f v2subtract(sf::Vector2f v1, sf::Vector2f v2)
    {
        return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
    }

    inline float v2lenght(sf::Vector2f v)
    {
        //√( x² + y² )
        return pow(v.x, 2) + pow(v.y, 2);
    }
    inline void v2scaleref(sf::Vector2f &v, float const &scale)
    {
        v.x *= scale;
        v.y *= scale;
    }
    inline void v2v2scaleref(sf::Vector2f &v1, sf::Vector2f &v2)
    {
        v1.x *= v2.x;
        v1.y *= v2.y;
    }
    inline void zero(sf::Vector2f &v)
    {
        v.x = 0;
        v.y = 0;
    }
    inline bool Collision_AABB(
    sf::RectangleShape &body1,
    sf::RectangleShape &body2,
    sf::Vector2f       &velocity)
    {
        
    }
    inline bool Collision_AABB(
    sf::RectangleShape &body1,
    sf::RectangleShape &body2)
    {
        
    }
    inline bool Collision_SAT(sf::RectangleShape &body1, sf::RectangleShape &body2)
    {

    }
    inline sf::Vector2i snapToGrid(int x, int y)
    {
        return sf::Vector2i(((int)x / GRID_SIZE)*GRID_SIZE,((int)y / GRID_SIZE)*GRID_SIZE);
    }
    inline sf::Vector2i snapToGrid(sf::Vector2i vec2i)
    {
        return snapToGrid(vec2i.x, vec2i.y);
    }
    inline sf::Vector2i snapToGrid(sf::Vector2f vec2f)
    {
        return snapToGrid(vec2f.x, vec2f.y);
    }
}