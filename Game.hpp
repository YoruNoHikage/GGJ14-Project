#ifndef GAME_HPP
#define GAME_HPP

#include <cmath>
#include <queue>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

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
        void startScreen();
        void gameLoop();

        void displayPath();
        void displayDistanceToPoint();
        void displayMonolog();

        static MonologQueue& getMonologQueue();

        bool _isExiting, _isPaused;
        bool _isRunning;

        sf::Texture _logoTex;

        sf::RenderWindow _app;
        Event *_event;

        sf::Event _currentEvent;
        sf::Clock _clock;
        sf::Music _music;

        // Objects in game
        World _world;

        // Display style (gradient)
        sf::VertexArray _background;
};


#endif // GAME_HPP
