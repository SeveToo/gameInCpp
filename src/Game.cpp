#include "Game.h"

void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxCoins = 10;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

// Constrictor and Destructor
Game::Game() 
{
    this->initVariables();
    this->initWindow();
}

Game::~Game() 
{
    delete this->window;
}

const bool Game::running() const 
{
    return this->window->isOpen();
}

// Functions =====================

void Game::pollEvents()
{
    while (this->window->pollEvent(this->sfmlEvent)) 
    {
        switch (this->sfmlEvent.type) 
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::spawnCoin() 
{
    // Timer
    if (this->spawnTimer < this->spawnTimerMax) 
    {
        this->spawnTimer += 1.f;
    }
    else 
    {
        if (this->coins.size() < this->maxCoins) 
        {
            this->coins.push_back(Coin(this->window));
            this->spawnTimer = 0.f;
        }
    }
}

void Game::update() 
{
    this->pollEvents();

    this->spawnCoin();
    this->player.update(this->window);
}

void Game::render() 
{
    this->window->clear();

    // Render stuff
    this->player.render(this->window);

    for(auto i : this->coins)
    {
        i.render(this->window);
    }

    this->window->display();
}
