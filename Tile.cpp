#include "Tile.hpp"

#include <iostream>

Tile::Tile() : _visited(false)
{
}

Tile::~Tile()
{
}

bool Tile::alreadyVisited()
{
    return _visited;
}

void Tile::visit()
{
    _visited = true;
}

void Tile::forgot()
{
    _visited = false;
}

void Tile::setPosition(int x, int y)
{
    _position.x = x;
    _position.y = y;
}

sf::Vector2i Tile::getPosition()
{
    return _position;
}
