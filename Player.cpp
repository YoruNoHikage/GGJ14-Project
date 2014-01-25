#include "Player.hpp"

Player::Player() : _position(sf::Vector2i(0, 0))
{
}

Player::~Player()
{
}

sf::Vector2i& Player::getPosition()
{
    return _position;
}

void Player::setPosition(int x, int y)
{
    _position.x = x;
    _position.y = y;
}

void Player::setPosition(sf::Vector2i position)
{
    _position = position;
}

Itineraire Player::getPath()
{
    return _path;
}

///@todo: delete
void Player::moveInWorld(int x, int y)
{
    if(x > 0 && y == 0)
        _path.push_back(LEFT);
    else if(x < 0 && y == 0)
        _path.push_back(RIGHT);
    else if(x == 0 && y > 0)
        _path.push_back(TOP);
    else if(x == 0 && y < 0)
        _path.push_back(BOT);

    if(_path.size() > 20)
        _path.erase(_path.begin());
}


