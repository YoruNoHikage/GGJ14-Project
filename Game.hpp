#ifndef GAME_HPP
#define GAME_HPP

#include <cmath>
#include <queue>
#include "SFML/Graphics.hpp"

#include "config.hpp"

#include "Monolog.hpp"
#include "Event.hpp"
#include "World.hpp"

typedef std::queue<Monolog*> MonologQueue;

class Game
{
    public:
        Game();
        ~Game();

        void start();

        static void addToMonologQueue(Monolog& monolog);
        static sf::Font& getFont();

    private:
        bool init();
        void gameLoop();

        void displayPath();
        void displayDistanceToPoint();
        void displayMonolog();

        static MonologQueue& getMonologQueue();

        bool _isExiting;

        sf::RenderWindow _app;
        sf::Font _fontQuicksand;
        Event *_event;

        sf::Event _currentEvent;
        sf::Clock _clock;

        // Objects in game
        World _world;

        // Display style (gradient)
        sf::VertexArray _background;
};


#endif // GAME_HPP
