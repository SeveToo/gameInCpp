#include "Coin.h"

void Coin::initShape(const sf::RenderWindow& window)
{
     this->shape.setRadius(10.f);
  sf::Color color(rand() % 255, rand() % 255, rand() % 255);
    this->shape.setFillColor(color);
    this->shape.setPosition(
      sf::Vector2f(
        static_cast<float>(rand()%window.getSize().x - this->shape.getGlobalBounds().width), 
        static_cast<float>(rand()%window.getSize().y - this->shape.getGlobalBounds().height)
        )
    );
}

Coin::Coin(const sf::RenderWindow* window)
{
    this->initShape(*window);
}

Coin::~Coin()
{

}

void Coin::update()
{

}

void Coin::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}