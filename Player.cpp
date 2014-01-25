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
