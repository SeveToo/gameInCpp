#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Coin
{
private:
    sf::CircleShape shape;

    void initShape(const sf::RenderWindow& window);

public:
    Coin(const sf::RenderWindow* window);
    virtual ~Coin();

    // Functions
    void update();
    void render(sf::RenderTarget* target);

};
