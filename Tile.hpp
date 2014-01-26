#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <SFML/System/Vector2.hpp>

/** \brief Representing one tile (as an obstacle or event)
 *         Abstract
 */
class Tile
{
    public:
        Tile();
        virtual ~Tile();

        // If we can walk on it
        virtual bool isWalkable() = 0;

        // When the player is walking on the tile
        virtual void onEnter() = 0;

        // When the player try to walk the tile
        virtual void onBump() = 0;

        // use it to draw on the terminal
        virtual char toChar() = 0;

        bool alreadyVisited();
        void visit();
        void forgot();

        sf::Vector2i getPosition();
        void setPosition(int x, int y);

    protected:

    private:
        bool _visited;

        sf::Vector2i _position;
};


#endif // TILE_HPP
