#include <iostream>

#include "lib/XMLNode.hpp"
#include "Monolog.hpp"
#include "Game.hpp"

Monolog::Monolog() : _currentLine(0), _isLoaded(false), _isFinished(false), _isPageToDraw(true)
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

        try
        {
            Node& page = root.firstChild("page");
            std::vector<Node*> linesPage = page.getChildren("line");
            for(std::vector<Node*>::iterator itr = linesPage.begin() ; itr != linesPage.end() ; ++itr)
            {
                _page.push_back((*itr)->getValue());
                std::cout << (*itr)->getValue() << std::endl;
            }
            _isPageToDraw = true;
        }
        catch(const std::runtime_error& e) { _isPageToDraw = false; }

        std::vector<Node*> lines = root.getChildren("line");
        for(std::vector<Node*>::iterator itr = lines.begin() ; itr != lines.end() ; ++itr)
        {
            _strings.push_back((*itr)->getValue());
            #ifdef DEBUG
            std::cout << (*itr)->getValue() << std::endl;
            #endif
        }

        _drawableText.setFont(Game::getFont());
        _drawableTextPage.setFont(Game::getFont());

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
    if(_page.size() != 0)
        _isPageToDraw = true;

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
    if(_isPageToDraw)
    {
        target.draw(_backgroundPage, states);
        target.draw(_drawableTextPage, states);
    }
    else
    {
        target.draw(_background, states);
        target.draw(_drawableText, states);
    }
}

void Monolog::nextLine()
{
    if(_isPageToDraw)
    {
        _isPageToDraw = false;
        updateDrawableText();
        return;
    }

    _currentLine++;
    if(_currentLine > _strings.size() - 1) // just security
    {
        _isPageToDraw = true;
        _currentLine = 0;
    }
    else if(_currentLine == _strings.size() - 1) // ends the monolog
        _isFinished = true;

    updateDrawableText();
}

void Monolog::updateDrawableText()
{
    if(_isLoaded)
    {
        if(_isPageToDraw)
        {
            sf::String line;
            for(unsigned int i(0) ; i < _page.size() ; i++)
                line += _page[i] + "\n";

            _drawableTextPage.setString(line);
            _drawableTextPage.setPosition(VIEW_WIDTH / 2 - _drawableTextPage.getGlobalBounds().width / 2, VIEW_HEIGHT / 2 - _drawableTextPage.getGlobalBounds().height / 2);

            int margin = 30;
            //_backgroundPage.setSize(sf::Vector2f(_drawableTextPage.getGlobalBounds().width + margin, VIEW_HEIGHT - margin));
            _backgroundPage.setSize(sf::Vector2f(VIEW_WIDTH + 100, VIEW_HEIGHT - VIEW_HEIGHT / 3));
            _backgroundPage.setOrigin(0, - _backgroundPage.getGlobalBounds().height -margin/4);
            //_backgroundPage.setPosition(_drawableTextPage.getPosition().x - margin/2, margin / 3);
            _backgroundPage.setPosition(-50, VIEW_HEIGHT / 6);
            _backgroundPage.setFillColor(sf::Color(0, 0, 0, 200));
            _backgroundPage.setCornersRadius(10);
            _backgroundPage.setCornerPointCount(5);
        }
        else
        {
            _drawableText.setString(_strings[_currentLine]);
            _drawableText.setPosition(VIEW_WIDTH / 2 - _drawableText.getGlobalBounds().width / 2, VIEW_HEIGHT * 3 / 4);

            int margin = 30;
            _background.setSize(sf::Vector2f(_drawableText.getGlobalBounds().width + margin, _drawableText.getGlobalBounds().height + margin));
            _background.setOrigin(0, - _background.getGlobalBounds().height -margin/4);
            if(_currentLine == 0 && _page.size() != 0) // WTF
                _background.setPosition(_drawableText.getPosition().x - margin/2, _drawableText.getPosition().y - margin/2 + 50);
            else
                _background.setPosition(_drawableText.getPosition().x - margin/2, _drawableText.getPosition().y - margin/2);
            _background.setFillColor(sf::Color(0, 0, 0, 200));
            _background.setCornersRadius(10);
            _background.setCornerPointCount(5);
        }
    }
}

