#include "Event.hpp"
#include "Game.hpp"

Event::Event(sf::RenderWindow &app) : _app(app), _type(DISTANCE), _text("", Game::getFont()) {}
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

void Event::display(sf::Vector2i nextTarget, sf::Vector2i playerPos, Itineraire pathPlayer)
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
