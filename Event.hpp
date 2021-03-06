#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <string>

#include "config.hpp"

#include "SFML/Graphics.hpp"

typedef enum EventType
{
    DISTANCE, HALO
} EventType;

class Event
{
    public :
        Event(sf::RenderWindow &app);
        ~Event();

        void display(sf::Vector2i nextTarget, sf::Vector2i playerPos, Itineraire pathPlayer);
        void changeEventType();
        void displayPath(Itineraire pathPlayer);

    private :
        void displayDistanceToPoint(sf::Vector2i nextTarget, sf::Vector2i playerPos);
        void displayHalo(sf::Vector2i nextTarget, sf::Vector2i playerPos);

        std::string numberToRoman(const int x);

        sf::RenderWindow& _app;
        EventType _type;
        sf::Text _text;

        sf::Texture _leftFootPrintTex;
        sf::Texture _rightFootPrintTex;
        sf::Texture _haloTex;
};

#endif // EVENT_HPP
