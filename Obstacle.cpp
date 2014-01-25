#include "Obstacle.hpp"

Obstacle::Obstacle()
{

}

Obstacle::~Obstacle()
{

}

bool Obstacle::isWalkable()
{
    return false;
}

void Obstacle::onEnter()
{
    // NO WAY
}

void Obstacle::onBump()
{
}

char Obstacle::toChar()
{
    return '*';
}
