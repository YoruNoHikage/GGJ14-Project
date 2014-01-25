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

Itineraire Player::getPath()
{
    return _path;
}

void Player::moveInWorld(int x, int y)
{
    if(x != 0)
    {
        _position.x += x;
        if(_position.x <= 0)
            _position.x = 0;
        else if(_position.x >= WORLD_WIDTH -1)
            _position.x = WORLD_WIDTH -1;
    }

    if(y != 0)
    {
        _position.y += y;
        if(_position.y <= 0)
            _position.y = 0;
        else if(_position.y >= WORLD_HEIGHT -1)
            _position.y = WORLD_HEIGHT -1;
    }

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


