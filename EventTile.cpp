#include "EventTile.hpp"

EventTile::EventTile()
{
}

EventTile::~EventTile()
{
}

bool EventTile::isWalkable()
{
    return true;
}

void EventTile::onEnter()
{
    // d�clencher l'event
}

void EventTile::onBump()
{
    // wait, what ?
}

char EventTile::toChar()
{
    return 'e';
}
