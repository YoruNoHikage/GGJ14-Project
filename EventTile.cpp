#include "EventTile.hpp"

#include "Game.hpp"

EventTile::EventTile() : _isActive(true), _isEventLoaded(false), _alreadyDisplayed(false), _id(0)
{
}

EventTile::EventTile(int id) : EventTile()
{
    setId(id);
}

EventTile::~EventTile()
{
}

bool EventTile::loadFromFile(const std::string& filename)
{
    _isEventLoaded = _monolog.loadFromFile(filename);

    return _isEventLoaded;
}

int EventTile::getId()
{
    return _id;
}

void EventTile::setId(int id)
{
    _id = id;
}

bool EventTile::isActive()
{
    return _isActive;
}

void EventTile::setActive(bool active)
{
    _isActive = active;
}

bool EventTile::isWalkable()
{
    return true;
}

void EventTile::onEnter()
{
    if(_isEventLoaded && !_alreadyDisplayed && _isActive)
    {
        _monolog.init();
        Game::addToMonologQueue(_monolog);
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
