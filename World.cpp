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

bool World::generate()
{
    // memory optimization
    _tiles.resize(WORLD_HEIGHT); // resizing directly to avoid too much allocation
    for(int i(0) ; i < WORLD_HEIGHT ; i++)
        _tiles[i].resize(WORLD_WIDTH);

    // Player start
    _player.setPosition(rand() % (WORLD_WIDTH - 1) + 1, rand() % (WORLD_HEIGHT - 1) + 1);
    std::cout << "Player position " << _player.getPosition().x << " ; " << _player.getPosition().y << std::endl;

    // algorithm generation
    for(int i(0) ; i < WORLD_HEIGHT ; i++)
        for(int j(0) ; j < WORLD_WIDTH ; j++)
        {
            // remplissage des tableaux
            _tiles[i][j] = new Tile(); ///@todo: update with the different inherited Tile
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
        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.moveInWorld(0, 1);
            markPosition();
            drawConsole();
        }*/
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _player.moveInWorld(0, -1);
            markPosition();
            drawConsole();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _player.moveInWorld(1, 0);
            markPosition();
            drawConsole();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _player.moveInWorld(-1, 0);
            markPosition();
            drawConsole();
        }
    }
}

void World::markPosition()
{
    _tiles[_player.getPosition().x][_player.getPosition().y]->visit();
}

Itineraire World::getPlayerPath()
{
    return _player.getPath();
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
            else if(_tiles[j][i]->alreadyVisited())
                std::cout << "+";
            else
                std::cout << "0";
        }
        std::cout << std::endl;
    }
}
