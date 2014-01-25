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

///@todo: circular world
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
}
