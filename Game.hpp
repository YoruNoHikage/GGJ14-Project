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
        bool init();
        void gameLoop();
        void displayPath();

        bool _isExiting;

        sf::RenderWindow _app;

        sf::Event _currentEvent;
        sf::Clock _clock;

        // Objects in game
        World _world;

        // Display style (gradient)
        sf::VertexArray _background;
};


#endif // GAME_HPP
