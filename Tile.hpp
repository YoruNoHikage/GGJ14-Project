#ifndef TILE_HPP
#define TILE_HPP

#include <string>

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

    protected:

    private:
        bool _visited;
};


#endif // TILE_HPP
