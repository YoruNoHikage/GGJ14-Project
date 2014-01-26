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
        void generatePositionTile(Tile* tile);

        bool update(sf::Time elapsedTime, bool pause);
        void markPosition();
        Itineraire getPlayerPath();

        void draw();
        void drawConsole(); // debug only

        sf::Vector2i getNextTarget();
        sf::Vector2i getPlayerPos();
        int getNbPas();
        void setNbPas(int nbPas);

    protected:

    private:
        Player _player;
        Array2DTile _tiles;
        sf::Vector2i _nextTarget;
        sf::Time _elapsedTime;
        int _nbPas;

        bool _isLoaded; // if not, we can't draw/use it
};


#endif // WORLD_HPP
