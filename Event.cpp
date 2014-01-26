#include "Event.hpp"

Event::Event(sf::RenderWindow &app, sf::Font &font) : _app(app), _font(font), _type(DISTANCE) {}
Event::~Event(){}


void Event::displayPath(Itineraire pathPlayer)
{
    sf::Vector2f size(PATH_WIDTH * 4/5, PATH_HEIGHT * 4/5);
    sf::Vector2f currPos;

    currPos.x = VIEW_WIDTH / 2 - PATH_WIDTH / 2;
    currPos.y = VIEW_HEIGHT / 2 - PATH_HEIGHT / 2;

    for(int i = pathPlayer.size(); i > 0; i--)
    {
        sf::RectangleShape square(size);
        square.setFillColor(sf::Color::Black);
        square.setPosition(currPos);

        _app.draw(square);

        if(pathPlayer[i] == TOP)
            currPos.y -= PATH_HEIGHT;
        else if(pathPlayer[i] == BOT)
            currPos.y += PATH_HEIGHT;
        else if(pathPlayer[i] == LEFT)
            currPos.x -= PATH_WIDTH;
        else if(pathPlayer[i] == RIGHT)
            currPos.x += PATH_WIDTH;
    }
}

void Event::displayDistanceToPoint(sf::Vector2i nextTarget, sf::Vector2i playerPos)
{
    sf::Text text;
    text.setFont(_font);

    int deltaX = abs(nextTarget.x - playerPos.x);
    if(deltaX > WORLD_WIDTH / 2)
        deltaX = WORLD_WIDTH - deltaX;

    int deltaY = abs(nextTarget.y - playerPos.y);
    if(deltaY > WORLD_HEIGHT / 2)
        deltaY = WORLD_HEIGHT - deltaY;

    int distance = deltaX + deltaY;

    text.setString(numberToRoman(distance));

    text.setColor(sf::Color::Black);

    text.setPosition(10, 10);
    _app.draw(text);
}

bool Event::display(sf::Vector2i nextTarget, sf::Vector2i playerPos, Itineraire pathPlayer)
{
    switch(_type)
    {
        case DISTANCE:
            displayDistanceToPoint(nextTarget, playerPos);
            break;
    }
}

void Event::changeEventType()
{
    if((rand() % 1) == 0)
        _type = DISTANCE;
    else
        _type = DISTANCE;
}
