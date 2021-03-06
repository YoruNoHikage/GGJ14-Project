#include "Game.hpp"

#include <iostream>

Game::Game() : _isExiting(false), _isPaused(false), _isRunning(false), _isFinished(false), _background(sf::Quads, 4)
{
    _background[0].position = sf::Vector2f(0, VIEW_HEIGHT / 2);
    _background[1].position = sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT / 2);
    _background[2].position = sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT);
    _background[3].position = sf::Vector2f(0, VIEW_HEIGHT);

    _background[0].color = _background[1].color = sf::Color(255, 255, 255, 0);
    _background[2].color = _background[3].color = sf::Color(0, 0, 0, 100);

    if(!getFont().loadFromFile("data/font/quicksand-l.otf"))
        exit(EXIT_FAILURE);

    if (!_music.openFromFile("data/sound/backsound.ogg"))
        exit(EXIT_FAILURE);

    if(!_logoTex.loadFromFile("data/img/logo.png"))
        exit(EXIT_FAILURE);
    _logoTex.setSmooth(true);

    _event = new Event(_app);
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

    sf::View view(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));
    _app.setView(view);

    std::srand(time(NULL));

    _app.setVerticalSyncEnabled(true);

    // Initialize screens
    /*_stateMachine.add("splashscreen", new SplashScreen(_stateMachine));
    _stateMachine.add("playingscreen", new PlayingScreen(_stateMachine));

    _stateMachine.change("splashscreen");*/ // do we have to use a state machine ?

    _music.play();
    _music.setLoop(true);

    if(!init())
        exit(EXIT_FAILURE);

    while(!_isExiting && !_isFinished)
    {
        if(_isRunning)
            gameLoop();
        else
            startScreen();
    }

    _app.close();
}

bool Game::init()
{
    return _world.generate();
}

void Game::startScreen()
{
    sf::Sprite spriteLogo;
    spriteLogo.setTexture(_logoTex);
    sf::Vector2f posLogo;

    posLogo.x = VIEW_WIDTH / 2 - spriteLogo.getLocalBounds().width / 2;
    posLogo.y = VIEW_HEIGHT / 2 - spriteLogo.getLocalBounds().height / 2;
    spriteLogo.setPosition(posLogo);

    while(_app.pollEvent(_currentEvent))
    {
        switch(_currentEvent.type)
        {
            case sf::Event::Closed:
                _isExiting = true;
                break;
            case sf::Event::KeyPressed:
                 if(_currentEvent.key.code != sf::Keyboard::Escape)
                    _isRunning = true;
                else
                    _isExiting = true;
                break;
        }
    }
    _app.clear(sf::Color::White);
    _app.draw(spriteLogo);
    _app.display();
}

void Game::gameLoop()
{
    while(_app.pollEvent(_currentEvent))
    {
        switch(_currentEvent.type)
        {
            case sf::Event::Closed:
                _isExiting = true;
                break;
            case sf::Event::KeyPressed:
                if(getMonologQueue().size() > 0)
                {
                    _isPaused = true;
                    if(_currentEvent.key.code == sf::Keyboard::Space)
                    {
                        if(getMonologQueue().front()->isFinished())
                            getMonologQueue().pop();
                        else
                            getMonologQueue().front()->nextLine();
                    }
                }
                else
                    _isPaused = false;

                if(_currentEvent.key.code == sf::Keyboard::Escape)
                    _isRunning = false;
                break;
        }
    }
    sf::Time elapsed = _clock.restart();

    if(_world.update(elapsed, _isPaused) && _world.getNbPas() == 0)
        _event->changeEventType();

    _app.clear(sf::Color::White);
    _app.draw(_background);

    _world.draw();
    displayPath();

    displayMonolog();

    _app.display();
}

void Game::displayPath()
{
    sf::Vector2f size(PATH_WIDTH * 4/5, PATH_HEIGHT * 4/5);
    sf::Vector2f currPos;

    if(_world.getNbPas() == 0)
        _event->display(_world.getNextTarget(), _world.getPlayerPos(), _world.getPlayerPath());

    _event->displayPath(_world.getPlayerPath());
}

void Game::displayMonolog()
{
    if(getMonologQueue().size() > 0)
    {
        Monolog* monolog = getMonologQueue().front();
        _app.draw(*monolog);
    }
    else if(_world.isLastMonolog() && getMonologQueue().size() <= 0)
    {
        _isFinished = true;
    }
}

void Game::addToMonologQueue(Monolog& monolog)
{
    // add to the queue
    MonologQueue& monologs = getMonologQueue();
    monologs.push(&monolog);
}

MonologQueue& Game::getMonologQueue()
{
    static MonologQueue* _monologs = new MonologQueue();
    return *_monologs;
}

sf::Font& Game::getFont()
{
    static sf::Font* font = new sf::Font();
    return *font;
}
