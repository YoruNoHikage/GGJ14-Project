#ifndef EVENT_TILE_HPP
#define EVENT_TILE_HPP

#include "Tile.hpp"

class EventTile : public Tile
{
    public:
        EventTile();
        ~EventTile();

        // If we can walk on it
        bool isWalkable();

        // When the player is walking on the tile
        void onEnter();

        // When the player try to walk the tile
        void onBump();

        // use it to draw on the terminal
        char toChar();
    protected:

    private:

};


#endif // EVENT_TILE_HPP
