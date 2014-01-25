#include "Game.hpp"

Game::Game() : _isExiting(false)
{
}

Game::~Game()
{
}

void Game::start()
{
    // Initialize tools
    //ImageManager *im = new ImageManager(); // do we need to use this in this project ?
    //Locator::provideImageManager(im);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _app.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Samsara", sf::Style::Default, settings);

    sf::View view = _app.getDefaultView();
    view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
    _app.setView(view);

    std::srand(time(NULL));

    _app.setVerticalSyncEnabled(true);

    // Initialize screens
    /*_stateMachine.add("splashscreen", new SplashScreen(_stateMachine));
    _stateMachine.add("playingscreen", new PlayingScreen(_stateMachine));

    _stateMachine.change("splashscreen");*/ // do we have to use a state machine ?

    if(!init())
        exit(EXIT_FAILURE);

    while(!_isExiting)
    {
        gameLoop();
    }

    _app.close();
}

bool Game::init()
{
    return _world.generate();
}

void Game::gameLoop()
{
    while(_app.pollEvent(_currentEvent))
    {
        switch(_currentEvent.type)
        {
            case sf::Event::Closed:
                _isExiting = true;
        }

    }
    sf::Time elapsed = _clock.restart();

    _world.update(elapsed);

    _app.clear(sf::Color::White);

    _world.draw();

    _app.display();
}
