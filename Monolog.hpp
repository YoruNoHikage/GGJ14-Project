#ifndef MONOLOG_HPP
#define MONOLOG_HPP

#include <vector>
#include <string>

#include "SFML/Graphics.hpp"

typedef std::vector<std::string> ArrayString;

class Monolog : public sf::Drawable
{
    public:
        Monolog();
        ~Monolog();

        bool loadFromFile(const std::string& filename);

        void init();

        bool isLoaded();
        bool isFinished();

        void nextLine();
        void updateDrawableText();

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        ArrayString _strings;
        unsigned int _currentLine;

        sf::Text _drawableText;
        sf::RectangleShape _background;

        bool _isLoaded, _isFinished;
};


#endif // MONOLOG_HPP
