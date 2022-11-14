#pragma once

#include <iostream>
  #include <ctime>
  #include <vector>
  #include <sstream>

  #include "Player.h"
  #include "Coin.h"

class Game {
  private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event sfmlEvent;

    Player player;
    int points;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    std::vector <Coin> coins;
    float spawnTimerMax;
    float spawnTimer;
    int maxCoins;

    void initVariables();
    void initWindow();
    void initFonts();
    void initText();

  public: 
    // Constrictor and Destructor
    Game();
    ~Game();

    // Accessors
    const bool& getEndGame() const;

    // Modifiers

    // Functions
    const bool running() const;
    void pollEvents();

    void spawnCoin();
    const int randBallType() const;
    void updatePlayer();
    void updateCollision();
    void updateGui();
    void update();

    void renderGui(sf::RenderTarget* target);
    void render();
};

