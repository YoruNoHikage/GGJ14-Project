#include <iostream>

#include "EmptyTile.hpp"

EmptyTile::EmptyTile()
{
}

EmptyTile::~EmptyTile()
{
}

bool EmptyTile::isWalkable()
{
    return true;
}

void EmptyTile::onEnter()
{
}

void EmptyTile::onBump()
{
}

char EmptyTile::toChar()
{
    return '0';
}
