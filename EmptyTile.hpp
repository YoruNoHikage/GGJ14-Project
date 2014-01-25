#ifndef EMPTY_TILE_HPP
#define EMPTY_TILE_HPP

#include "Tile.hpp"

class EmptyTile : public Tile
{
    public:
        EmptyTile();
        ~EmptyTile();

        bool isWalkable();

        void onEnter();

        void onBump();

        char toChar();
    protected:

    private:

};


#endif // EMPTY_TILE_HPP
