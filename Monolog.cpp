#include <iostream>

#include "lib/XMLNode.hpp"
#include "Monolog.hpp"
#include "Game.hpp"

Monolog::Monolog() : _currentLine(0), _isLoaded(false), _isFinished(false)
{
}

Monolog::~Monolog()
{
}

bool Monolog::loadFromFile(const std::string& filename)
{
    XMLNode root;

    try
    {
        root.loadFromFile(filename);

        std::vector<Node*> lines = root.getChildren("line");
        for(std::vector<Node*>::iterator itr = lines.begin() ; itr != lines.end() ; ++itr)
        {
            _strings.push_back((*itr)->getValue());
            #ifdef DEBUG
            std::cout << (*itr)->getValue() << std::endl;
            #endif
        }

        _drawableText.setFont(Game::getFont());

        _isLoaded = true;

        updateDrawableText();

    }
    catch(std::exception const& e)
    {
        _strings.push_back(e.what());
        #ifdef DEBUG
        std::cout << e.what() << std::endl;
        #endif
    }

    return true;
}

void Monolog::init()
{
    _currentLine = 0;
    _isFinished = false;

    updateDrawableText();
}

bool Monolog::isLoaded()
{
    return _isLoaded;
}

bool Monolog::isFinished()
{
    return _isFinished;
}

void Monolog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_background, states);
    target.draw(_drawableText, states);
}

void Monolog::nextLine()
{
    _currentLine++;
    if(_currentLine > _strings.size() - 1) // just security
        _currentLine = 0;
    else if(_currentLine == _strings.size() - 1) // ends the monolog
        _isFinished = true;

    updateDrawableText();
}

void Monolog::updateDrawableText()
{
    if(_isLoaded)
    {
        _drawableText.setString(_strings[_currentLine]);
        _drawableText.setPosition(VIEW_WIDTH / 2 - _drawableText.getGlobalBounds().width / 2, VIEW_HEIGHT * 3 / 4);

        int margin = 30;
        _background.setSize(sf::Vector2f(_drawableText.getGlobalBounds().width + margin, _drawableText.getGlobalBounds().height + margin));
        _background.setOrigin(0, - _background.getGlobalBounds().height -margin/4);
        _background.setPosition(_drawableText.getPosition().x - margin/2, _drawableText.getPosition().y - margin/2);
        _background.setFillColor(sf::Color(0, 0, 0, 200));
        _background.setCornersRadius(10);
        _background.setCornerPointCount(5);
    }
}

