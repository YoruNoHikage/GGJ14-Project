#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"

#include "config.hpp"

#include "World.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void start();

    private:
        void gameLoop();

        bool _isExiting;

        sf::RenderWindow _app;

        sf::Event _currentEvent;
        sf::Clock _clock;

        // Objects in game
        World _world;
};


#endif // GAME_HPP
