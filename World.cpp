#include "World.hpp"

#include <iostream>
#include <ctime>

World::World() : _elapsedTime(sf::Time::Zero)
{
}

World::~World()
{
    for(int i(0) ; i < _tiles.size() ; i++)
        for(int j(0) ; j < _tiles[i].size() ; j++)
            delete _tiles[i][j];
}

bool World::generateWorld()
{
    // memory optimization
    _tiles.resize(WORLD_HEIGHT); // resizing directly to avoid too much allocation
    for(int i(0) ; i < WORLD_HEIGHT ; i++)
        _tiles[i].resize(WORLD_WIDTH);

    // algorithm generation
    for(int i(0) ; i < WORLD_HEIGHT ; i++)
        for(int j(0) ; j < WORLD_WIDTH ; j++)
        {
            // remplissage des tableaux
            _tiles[i][j] = new Tile(); ///@todo: update with the different inherited Tile
            // rand % (WINDOW_HEIGHT - 1) + 1

            // start tile

            // end tile
        }

    return true;
}

void World::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;

    if(_elapsedTime >= sf::milliseconds(100))
    {
        _elapsedTime = sf::Time::Zero;

        // Player moves in the world
        ///@todo: collisions
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.moveInWorld(0, 1);
            drawConsole();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _player.moveInWorld(0, -1);
            drawConsole();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _player.moveInWorld(1, 0);
            drawConsole();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _player.moveInWorld(-1, 0);
            drawConsole();
        }
    }
}

void World::draw()
{
}

void World::drawConsole()
{
    system("cls");
    for(int i(0) ; i < WORLD_HEIGHT ; i++)
    {
        for(int j(0) ; j < WORLD_WIDTH ; j++)
        {
            if(_player.getPosition().y == i && _player.getPosition().x == j)
                std::cout << "X";
            else
                std::cout << "0";
        }

        std::cout << std::endl;
    }
}
