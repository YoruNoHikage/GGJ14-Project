#include "Event.hpp"
#include "Game.hpp"

Event::Event(sf::RenderWindow &app) : _app(app), _type(DISTANCE), _text("", Game::getFont())
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
    int deltaX = abs(nextTarget.x - playerPos.x);
    if(deltaX > WORLD_WIDTH / 2)
        deltaX = WORLD_WIDTH - deltaX;

    int deltaY = abs(nextTarget.y - playerPos.y);
    if(deltaY > WORLD_HEIGHT / 2)
        deltaY = WORLD_HEIGHT - deltaY;

    int distance = deltaX + deltaY;

    _text.setString(numberToRoman(distance));

    _text.setColor(sf::Color::Black);

    _text.setPosition(10, 10);
    _app.draw(_text);
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

void Event::display(sf::Vector2i nextTarget, sf::Vector2i playerPos, Itineraire pathPlayer)
{
    switch(_type)
    {
        case DISTANCE:
            displayDistanceToPoint(nextTarget, playerPos);
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

std::string Event::numberToRoman(const int x)
{
	//assert(x < 5000);

	std::string result;
	int val = x;

    int tmp = val / 1000;
	for(int i = 0; i < tmp; i++)
	{
		result.append("M");
		val -= 1000;
	}

	if (val / 900 > 0)
	{
		result.append("CM");
		val -= 900;
	}

	if (val / 500 > 0)
	{
		result.append("D");
		val -= 500;
	}

	if (val / 400 > 0)
	{
		result.append("CD");
		val -= 400;
	}

    tmp = val / 100;
	for(int i = 0; i < tmp; i++)
	{
		result.append("C");
		val -= 100;
	}

	if (val / 90 > 0)
	{
		result.append("XC");
		val -= 90;
	}

	if (val / 50 > 0)
	{
		result.append("L");
		val -= 50;
	}

	if (val / 40 > 0)
	{
		result.append("XL");
		val -= 40;
	}

    tmp = val / 10;
	for(int i = 0; i < tmp; i++)
	{
		result.append("X");
		val -= 10;
	}

	if (val / 9 > 0)
	{
		result.append("IX");
		val -= 9;
	}

	if (val / 5 > 0)
	{
		result.append("V");
		val -= 5;
	}

	if (val / 4 > 0)
	{
		result.append("IV");
		val -= 4;
	}

	for(int i = 0; i < val; i++)
		result.append("I");

	return result;
}
