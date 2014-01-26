#include "Game.hpp"
#include "numberToRoman.hpp"

#include <iostream>

Game::Game() : _isExiting(false), _background(sf::Quads, 4)
{
    _background[0].position = sf::Vector2f(0, VIEW_HEIGHT / 2);
    _background[1].position = sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT / 2);
    _background[2].position = sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT);
    _background[3].position = sf::Vector2f(0, VIEW_HEIGHT);

    _background[0].color = _background[1].color = sf::Color(255, 255, 255, 0);
    _background[2].color = _background[3].color = sf::Color(0, 0, 0, 100);

    if (!_fontQuicksand.loadFromFile("quicksand.otf"))
        exit(EXIT_FAILURE);

    if(!getFont().loadFromFile("quicksand.otf"))
        exit(EXIT_FAILURE);
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
                break;
            case sf::Event::KeyPressed:
                /*if(getMonologQueue().size() > 0 && )
                {

                }*/
                break;
        }

    }
    sf::Time elapsed = _clock.restart();

    _world.update(elapsed);

    _app.clear(sf::Color::White);
    _app.draw(_background);

    _world.draw();
    displayPath();
    displayDistanceToPoint();

    displayMonolog();

    _app.display();
}

void Game::displayPath()
{
    sf::Vector2f size(PATH_WIDTH * 4/5, PATH_HEIGHT * 4/5);
    sf::Vector2f currPos;

    currPos.x = VIEW_WIDTH / 2 - PATH_WIDTH / 2;
    currPos.y = VIEW_HEIGHT / 2 - PATH_HEIGHT / 2;


    Itineraire pathPlayer = _world.getPlayerPath();

    for(int i = pathPlayer.size(); i > 0; i--)
    {
        sf::RectangleShape square(size);
        square.setFillColor(sf::Color::Black);
        square.setPosition(currPos);

        _app.draw(square);

        if(pathPlayer[i] == TOP)
            currPos.y -= PATH_HEIGHT;
        else if(pathPlayer[i] == BOT)
            currPos.y += PATH_HEIGHT;
        else if(pathPlayer[i] == LEFT)
            currPos.x -= PATH_WIDTH;
        else if(pathPlayer[i] == RIGHT)
            currPos.x += PATH_WIDTH;
    }
}

void Game::displayDistanceToPoint()
{
    sf::Text text;
    text.setFont(_fontQuicksand);

    //std::cout << _world.getNextTarget().x << std::endl;

    int deltaX = abs(_world.getNextTarget().x - _world.getPlayerPos().x);
    if(deltaX > WORLD_WIDTH / 2)
        deltaX = WORLD_WIDTH - deltaX;

    int deltaY = abs(_world.getNextTarget().y - _world.getPlayerPos().y);
    if(deltaY > WORLD_HEIGHT / 2)
        deltaY = WORLD_HEIGHT - deltaY;

    int distance = deltaX + deltaY;


    text.setString(numberToRoman(distance));

    text.setColor(sf::Color::Black);

    text.setPosition(10, 10);
    _app.draw(text);
}

void Game::displayMonolog()
{
    if(getMonologQueue().size() > 0)
    {
        Monolog* monolog = getMonologQueue().front();
        _app.draw(*monolog);

        // condition to do
        //getMonologQueue().pop();
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
