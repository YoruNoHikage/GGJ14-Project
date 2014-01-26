#include "Event.hpp"

Event::Event(sf::RenderWindow &app, sf::Font &font) : _app(app), _font(font), _type(DISTANCE)
{
    if(!_haloTex.loadFromFile("halo.png"))
        exit(EXIT_FAILURE);
    /*if(!_leftFootPrintTex.loadFromFile("pas-gauche.png"))
        exit(EXIT_FAILURE);
    if(!_rightFootPrintTex.loadFromFile("pas-droit.png"))
        exit(EXIT_FAILURE);*/

}

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
        sf::CircleShape circle(size.x * 0.5);

        square.setFillColor(sf::Color::Black);
        circle.setFillColor(sf::Color::Black);

        square.setPosition(currPos);
        circle.setPosition(currPos);

        if(i == pathPlayer.size())
            _app.draw(square);
        else
            _app.draw(circle);

        if(pathPlayer[i] == BOT)
            currPos.y -= PATH_HEIGHT;
        else if(pathPlayer[i] == TOP)
            currPos.y += PATH_HEIGHT;
        else if(pathPlayer[i] == RIGHT)
            currPos.x -= PATH_WIDTH;
        else if(pathPlayer[i] == LEFT)
            currPos.x += PATH_WIDTH;
    }

    /* si images de pieds
    sf::Vector2f currPos;
    sf::Sprite spriteFoot;

    spriteFoot.setTexture(_leftFootPrintTex);

    currPos.x = VIEW_WIDTH / 2 - PATH_WIDTH / 2;
    currPos.y = VIEW_HEIGHT / 2 - PATH_HEIGHT / 2;

    for(int i = pathPlayer.size(); i > 0; i--)
    {
        spriteFoot.setPosition(currPos);

        if(pathPlayer[i] == BOT)
        {
            currPos.y -= PATH_HEIGHT;
        }
        else if(pathPlayer[i] == TOP)
            currPos.y += PATH_HEIGHT;
        else if(pathPlayer[i] == RIGHT)
        {
            currPos.x -= PATH_WIDTH;
        }
        else if(pathPlayer[i] == LEFT)
        {
            currPos.x += PATH_WIDTH;
        }
        _app.draw(spriteFoot);
    }*/
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

void Event::displayHalo(sf::Vector2i nextTarget, sf::Vector2i playerPos)
{
    sf::Vector2f currPos;
    sf::Sprite spriteHalo;

    spriteHalo.setTexture(_haloTex);

    Direction directionX, directionY, directionToGo;

    int deltaX = nextTarget.x - playerPos.x;
    if(abs(deltaX) < WORLD_WIDTH / 2)
    {
        if(deltaX > 0)
            directionX = RIGHT;
        else
            directionX = LEFT;
    }
    else
    {
        if(deltaX > 0)
            directionX = LEFT;
        else
            directionX = RIGHT;
    }

    int deltaY = nextTarget.y - playerPos.y;
    if(abs(deltaY) < WORLD_HEIGHT / 2)
    {
        if(deltaY > 0)
            directionY = BOT;
        else
            directionY = TOP;
    }
    else
    {
        if(deltaY > 0)
            directionY = TOP;
        else
            directionY = BOT;
    }

    if(abs(deltaX) > abs(deltaY))
        directionToGo = directionX;
    else
        directionToGo = directionY;

    switch(directionToGo)
    {
        case TOP :
            currPos.x = VIEW_WIDTH / 2 - spriteHalo.getLocalBounds().width / 2;
            currPos.y = - spriteHalo.getLocalBounds().height / 2;
            break;
        case BOT :
            currPos.x = VIEW_WIDTH / 2 - spriteHalo.getLocalBounds().width / 2;
            currPos.y = VIEW_HEIGHT - spriteHalo.getLocalBounds().height / 2;
            break;
        case LEFT :
            currPos.x = -spriteHalo.getLocalBounds().width / 2;
            currPos.y = VIEW_HEIGHT / 2 - spriteHalo.getLocalBounds().height / 2;
            break;
        case RIGHT :
            currPos.x = VIEW_WIDTH - spriteHalo.getLocalBounds().width / 2;
            currPos.y = VIEW_HEIGHT / 2 - spriteHalo.getLocalBounds().height / 2;
            break;
    }
    spriteHalo.setPosition(currPos);

    _app.draw(spriteHalo);
}

bool Event::display(sf::Vector2i nextTarget, sf::Vector2i playerPos, Itineraire pathPlayer)
{
    switch(_type)
    {
        case DISTANCE:
            //displayDistanceToPoint(nextTarget, playerPos);
            displayHalo(nextTarget, playerPos);
            break;
        case HALO:
            displayHalo(nextTarget, playerPos);
            break;
    }
}

void Event::changeEventType()
{
    if((rand() % 2) == 1)
        _type = DISTANCE;
    else
        _type = HALO;
}
