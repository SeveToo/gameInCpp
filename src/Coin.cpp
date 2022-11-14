#include "Coin.h"

void Coin::initShape(const sf::RenderWindow& window)
{
    this->shape.setRadius(10.f);

    sf::Color color;

    switch (this->type)
    {
        case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
    }

    this->shape.setFillColor(color);
    this->shape.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->shape.getGlobalBounds().width)),
        static_cast<float>(rand() % static_cast<int>(window.getSize().y - this->shape.getGlobalBounds().height))
    );
}

Coin::Coin(const sf::RenderWindow& window, int type)
{
    this->type = type;
    this->initShape(window);
}

Coin::~Coin()
{

}

const sf::CircleShape Coin::getShape() const
{
    return this->shape;
}

const int & Coin::getType() const
{
    return this->type;
}

void Coin::update()
{

}

void Coin::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}