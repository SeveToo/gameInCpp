#include "Game.h"

sf::Color theme = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
sf::Color black  = sf::Color(0,0,0);
sf::RectangleShape top;
int keyEffect = 0;

void Game::initVariables() {
    top.setFillColor(theme);
    top.setSize(sf::Vector2f(780,580));
    top.setPosition(sf::Vector2f(10,10));
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxCoins = 10;
    this->points = 0;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (!this->font.loadFromFile("assets/PixellettersFull.ttf")) {
        throw("Czcionka \"PixellettersFull.ttf\" nie mogła zostać załadowana"); 
    }
}

void Game::initText() {
    // GUI text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(32);

    // End game text init
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(sf::Vector2f(20.f, 100.f));
    this->endGameText.setString("KONIEC GRY");
}

// Constrictor and Destructor
Game::Game() 
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game() 
{
    delete this->window;
}

const bool & Game::getEndGame() const {
    return this->endGame;
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
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->coins.size() < this->maxCoins)
		{
			this->coins.push_back(Coin(*this->window, this->randBallType()));

            std::cout << "Coins size: " << this->coins.size() << "\n";

			this->spawnTimer = 0.f;
		}	
	}
}

const int Game::randBallType() const 
{
    int type = BallTypes::DEFAULT;
	
	int randValue = rand() % 100 + 1;
	if (randValue > 50 && randValue <= 60)
        type = BallTypes::KEY;
	if (randValue > 60 && randValue <= 80)
		type = BallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = BallTypes::HEALING;

	return type;
}

void Game::updatePlayer()
{
    this->player.update(this->window);

    if(this->player.getHp() <= 0) {
        this->endGame = true;
    }
}


void Game::updateCollision() 
{
    // Check the collision
    for (size_t i = 0; i < this->coins.size(); i++) 
    {
        if (this->player.getShape().getGlobalBounds().intersects(this->coins[i].getShape().getGlobalBounds())) 
        {
            switch (this->coins[i].getType()) 
            {
            case 0:
                this->points++;
                theme = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
                break;
            case 1:
                this->player.takeDamage(1);
                break;
            case 2:
                this->player.gainHealth(1);
                break;
            case 3:
                keyEffect = 500;
                break;
            }
            
            // Delete the coin
            this->coins.erase(this->coins.begin() + i);
            break;
        }
    }
    for (size_t i = 0; i < this->coins.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->coins[i].getShape().getGlobalBounds()))
		{
			switch (this->coins[i].getType())
			{
			case BallTypes::DEFAULT:
				this->points++;
				break;
			case BallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case BallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			//Remove the ball
			this->coins.erase(this->coins.begin() + i);			
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << " - Points: " << this->points << "\n"
		<< " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n"
		<< " - Key Effect: " << keyEffect << "\n";

	this->guiText.setString(ss.str());
}

void Game::update() 
{
    this->pollEvents();

    if(!this->endGame) {
        this->spawnCoin();
        this->updatePlayer();
        this->updateCollision();
        this->updateGui();
    }
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render() 
{
    
    if(keyEffect>0){
        keyEffect--;
        this->window->clear(theme);
        this->window->draw(top);
        top.setFillColor(theme);
    }else{
        this->window->clear(black);
        this->window->draw(top);
        top.setFillColor(theme);
    }

    


    // Render stuff
    this->player.render(this->window);

    for(auto i : this->coins)
    {
        i.render(*this->window);
    }

    // Render GUI
    this->renderGui(this->window);

    // Render end game text
    if(this->endGame) {
        this->window->draw(this->endGameText);
    }

    this->window->display();
}
