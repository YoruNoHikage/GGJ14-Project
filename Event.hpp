#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include "config.hpp"
#include "SFML/Graphics.hpp"
#include "numberToRoman.hpp"

typedef enum eventType
{
    DISTANCE
}eventType;

class Event
{
    public :
        Event(sf::RenderWindow &app, sf::Font &font);
        ~Event();

        bool display(sf::Vector2i nextTarget, sf::Vector2i playerPos, Itineraire pathPlayer);
        void changeEventType();
        void displayPath(Itineraire pathPlayer);

    private :
        void displayDistanceToPoint(sf::Vector2i nextTarget, sf::Vector2i playerPos);

        sf::RenderWindow& _app;
        sf::Font& _font;
        eventType _type;
};

#endif // EVENT_HPP
