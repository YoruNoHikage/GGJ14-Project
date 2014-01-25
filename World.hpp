#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "SFML/Graphics.hpp"

#include "config.hpp"

#include "EmptyTile.hpp"
#include "Player.hpp"

typedef std::vector<Tile*> ArrayTile;
typedef std::vector<ArrayTile> Array2DTile;

/** \brief This is the World where the player is
 */
class World
{
    public:
        World();
        ~World();

        bool generate();

        void update(sf::Time elapsedTime);
        void markPosition();
        Itineraire getPlayerPath();

        void draw();

        void drawConsole(); // debug only
    protected:

    private:
        Player _player;
        Array2DTile _tiles;

        sf::Time _elapsedTime;

        bool _isLoaded; // if not, we can't draw/use it
};


#endif // WORLD_HPP
