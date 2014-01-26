#ifndef EVENT_TILE_HPP
#define EVENT_TILE_HPP

#include "Tile.hpp"
#include "Monolog.hpp"

class EventTile : public Tile
{
    public:
        EventTile();
        EventTile(int id);
        ~EventTile();

        bool loadFromFile(const std::string& filename);

        int getId();
        void setId(int id);

        bool isActive();
        void setActive(bool active);

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
        int _id;
        Monolog _monolog;

        bool _isActive;
        bool _isEventLoaded;
        bool _alreadyDisplayed;
};


#endif // EVENT_TILE_HPP
