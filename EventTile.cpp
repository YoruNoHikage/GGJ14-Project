#include "EventTile.hpp"

#include "Game.hpp"

EventTile::EventTile() : _isEventLoaded(false), _alreadyDisplayed(false)
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
    if(_isEventLoaded || !_alreadyDisplayed)
    {
        Game::displayMonolog(_monolog);
        _alreadyDisplayed = true;
    }
}

void EventTile::onBump()
{
    // wait, what ?
}

char EventTile::toChar()
{
    return 'e';
}

