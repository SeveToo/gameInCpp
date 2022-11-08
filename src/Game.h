#pragma once

#include <iostream>
  #include <ctime>
  #include <vector>

  #include "Player.h"
  #include "Coin.h"

class Game {
  private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event sfmlEvent;

    Player player;

    std::vector <Coin> coins;
    float spawnTimerMax;
    float spawnTimer;
    int maxCoins;

    void initVariables();
    void initWindow();

  public: 
    // Constrictor and Destructor
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Functions
    const bool running() const;
    void pollEvents();

    void spawnCoin();
    void update();
    void render();


};

