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
    // déclencher l'event
}

void EventTile::onBump()
{
    // wait, what ?
}

char EventTile::toChar()
{
    return 'e';
}
