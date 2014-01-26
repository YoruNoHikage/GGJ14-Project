#include "EventTile.hpp"

EventTile::EventTile() : _isEventLoaded(false)
{
}

EventTile::~EventTile()
{
}

bool EventTile::loadFromFile(const std::string& filename)
{
    _isEventLoaded = _monolog.loadFromFile(filename);

    return _isEventLoaded;
}

bool EventTile::isWalkable()
{
    return true;
}

void EventTile::onEnter()
{
    /*if(_isEventLoaded)
        Game::displayMonolog(_monolog);*/
}

void EventTile::onBump()
{
    // wait, what ?
}

char EventTile::toChar()
{
    return 'e';
}

