#include <iostream>

#include "lib/XMLNode.hpp"&
#include "Monolog.hpp"
#include "Game.hpp"

Monolog::Monolog() : _isLoaded(false), _currentString(0)
{
}

Monolog::~Monolog()
{

}

bool Monolog::loadFromFile(const std::string& filename)
{
    std::cout << "Monolog : loading " << filename << std::endl;
    XMLNode root;

    try
    {
        root.loadFromFile(filename);

        std::vector<Node*> lines = root.getChildren("line");
        for(std::vector<Node*>::iterator itr = lines.begin() ; itr != lines.end() ; ++itr)
        {
            _strings.push_back((*itr)->getValue());
            std::cout << (*itr)->getValue() << std::endl;
        }

        _drawableText.setFont(Game::getFont());
        _drawableText.setString(_strings[_currentString]);
        _drawableText.setPosition(500, 500);

        _background.setSize(sf::Vector2f(_drawableText.getGlobalBounds().width + 20, _drawableText.getGlobalBounds().height + 20));
        _background.setPosition(_drawableText.getGlobalBounds().left - 10, _drawableText.getGlobalBounds().top - 10);
        _background.setFillColor(sf::Color(0, 0, 0, 150));

        _isLoaded = true;

    }
    catch(std::exception const& e)
    {
        _strings.push_back(e.what());
        std::cout << e.what() << std::endl;
    }

    return true;
}

bool Monolog::isLoaded()
{
    return _isLoaded;
}

void Monolog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_background, states);
    target.draw(_drawableText, states);
}
