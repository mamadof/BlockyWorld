#include <SFML/Graphics.hpp>
#include "info.hpp"
#include <math.h>

using namespace std;
namespace gm{ //stands for game math
    inline float v2distance(sf::Vector2f v1, sf::Vector2f v2)
    {
        //d=√((x2 – x1)² + (y2 – y1)²)
        float result = sqrtf((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
        return result;
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
    inline sf::Vector2f v2v2scale(sf::Vector2f v1, sf::Vector2f v2)
    {
        return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
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
        return false;
    }
    inline bool Collision_AABB(
    sf::RectangleShape &body1,
    sf::RectangleShape &body2)
    {
        return false;
    }
    inline bool Collision_SAT(sf::RectangleShape &body1, sf::RectangleShape &body2)
    {
        return false;
    }
    inline sf::Vector2f snapToGrid(int x, int y)
    {
        if (x < 0)x += -1 * GRID_SIZE;
        if (y < 0)y += -1 * GRID_SIZE;
        int xGrid = (int)(x / GRID_SIZE) * GRID_SIZE;
        int yGrid = (int)(y / GRID_SIZE) * GRID_SIZE;
        return sf::Vector2f(xGrid,yGrid);
    }
    inline sf::Vector2f snapToGrid(sf::Vector2f vec2f)
    {
        return snapToGrid(vec2f.x, vec2f.y);
    }
    inline sf::Vector2f snapToGrid(sf::Vector2i vec2i)
    {
        return snapToGrid(vec2i.x, vec2i.y);
    }

    inline sf::Vector2f v2MoveTowards(sf::Vector2f v, sf::Vector2f target, float maxDistance)
    {
        sf::Vector2f result(0,0);

        float dx = target.x - v.x;
        float dy = target.y - v.y;
        float value = (dx*dx) + (dy*dy);

        if ((value == 0) || ((maxDistance >= 0) && (value <= maxDistance*maxDistance))) return target;

        float dist = sqrtf(value);

        result.x = v.x + dx/dist*maxDistance;
        result.y = v.y + dy/dist*maxDistance;

        return result;
    }


    inline sf::Vector2f v2Rotate(sf::Vector2f v, float angle)
    {
        sf::Vector2f result(0,0);

        float cosres = cosf(angle);
        float sinres = sinf(angle);

        result.x = v.x*cosres - v.y*sinres;
        result.y = v.x*sinres + v.y*cosres;

        return result;
    }

    inline sf::Vector2f v2Normalize(sf::Vector2f v)
    {
        sf::Vector2f result(0,0);
        float length = sqrtf((v.x*v.x) + (v.y*v.y));

        if (length > 0)
        {
            float ilength = 1.0f/length;
            result.x = v.x*ilength;
            result.y = v.y*ilength;
        }

        return result;
    }

    inline sf::Vector2f v2ForceTowards(sf::Vector2f v, sf::Vector2f target, float multyplyer)
    {
        sf::Vector2f normalized = v2Normalize(target - v);
        return normalized * multyplyer;
    }
}