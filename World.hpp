#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "Tile.hpp"

typedef std::vector< std::vector<Tile*> > ArrayTile;

class World
{
    public:
        World();
        ~World();

        bool generateWorld();

        void update();

        void draw();
    protected:

    private:
        ArrayTile _tiles;

        bool _isLoaded; // if not, we can't draw/use it
};


#endif // WORLD_HPP
