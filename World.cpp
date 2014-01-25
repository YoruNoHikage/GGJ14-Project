#include "World.hpp"

#include <iostream>
#include <ctime>

#include "EventTile.hpp"

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

    // algorithm generation

    int xTmp = rand() % (WORLD_WIDTH - 1) + 1;
    int yTmp = rand() % (WORLD_HEIGHT - 1) + 1;
    _tiles[yTmp][xTmp] = new EventTile();

    _nextTarget.x = xTmp;
    _nextTarget.y = yTmp;

    //std::cout << _nextTarget.x << std::endl;


    for(int i(0) ; i < WORLD_HEIGHT ; i++)
        for(int j(0) ; j < WORLD_WIDTH ; j++)
        {
            // remplissage du reste avec des tiles vide
            if(_tiles[i][j] == NULL)
                _tiles[i][j] = new EmptyTile(); ///@todo: update with the different inherited Tile
        }

    _isLoaded = true;

    return true;
}

void World::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;

    if(_elapsedTime >= sf::milliseconds(100))
    {
        _elapsedTime = sf::Time::Zero;

        // Player moves in the world
        sf::Vector2i oldPosition(_player.getPosition());
        sf::Vector2i newPosition(oldPosition);

        int deltaX(0), deltaY(0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            deltaY = 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            deltaY = -1;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            deltaX = 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            deltaX = -1;

        ///@todo: delete
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _player.moveInWorld(0, 1);
            markPosition();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _player.moveInWorld(0, -1);
            markPosition();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _player.moveInWorld(1, 0);
            markPosition();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _player.moveInWorld(-1, 0);
            markPosition();
        }
        /// end todo

        if(deltaX != 0 || deltaY != 0)
        {
            // updating positions
            newPosition.x += deltaX;
            newPosition.y += deltaY;

            // circular map
            if(newPosition.x >= WORLD_WIDTH)
                newPosition.x = 0;
            else if(newPosition.x < 0)
                newPosition.x = WORLD_WIDTH -1;

            if(newPosition.y >= WORLD_HEIGHT)
                newPosition.y = 0;
            else if(newPosition.y < 0)
                newPosition.y = WORLD_HEIGHT -1;

            // bumping with an obstacle
            if(!_tiles[newPosition.y][newPosition.x]->isWalkable())
            {
                _tiles[newPosition.y][newPosition.x]->onBump();
                newPosition = oldPosition;
            }

            _player.setPosition(newPosition);

            // if player moved
            if(oldPosition != newPosition)
            {
                _tiles[newPosition.y][newPosition.x]->onEnter();
                drawConsole();
            }
        }
    }
}

void World::markPosition()
{
    _tiles[_player.getPosition().y][_player.getPosition().x]->visit();
}

Itineraire World::getPlayerPath()
{
    return _player.getPath();
}

sf::Vector2i World::getNextTarget()
{
    return _nextTarget;
}

sf::Vector2i World::getPlayerPos()
{
    return _player.getPosition();
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
            else if(_tiles[i][j]->alreadyVisited())
                std::cout << "+";
            else
                std::cout << _tiles[i][j]->toChar();
        }
        std::cout << std::endl;
    }
}
