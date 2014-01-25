#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Tile.hpp"

/** \brief Tree, rock etc...
 *         May be abstract some day
 */
class Obstacle : public Tile
{
    public:
        Obstacle();
        ~Obstacle();

        bool isWalkable();

        void onEnter();

        void onBump();

        char toChar();
    protected:

    private:

};


#endif // OBSTACLE_HPP
