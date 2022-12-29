#include "Coin.h"

sf::Texture coin_T;
sf::Texture bug_T;
sf::Texture heart_T;
sf::Texture key_T;


extern int keyEffect;

void assets(){
    coin_T.loadFromFile("assets/coin.png");
    heart_T.loadFromFile("assets/heart.png");
    bug_T.loadFromFile("assets/bug.png");
    key_T.loadFromFile("assets/key.png");


}

void Coin::initShape(const sf::RenderWindow& window)
{
    this->shape.setRadius(10.f);

    sf::Color color;

    switch (this->type)
    {
        case DEFAULT:
		//color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
        this->shape.setTexture(&coin_T);
		break;
	case DAMAGING:
        this->shape.setTexture(&bug_T);

		break;
	case HEALING:
        this->shape.setTexture(&heart_T);

		break;
    case KEY:
        this->shape.setTexture(&key_T);

        break;
    }

    
    this->shape.setPosition(
        static_cast<float>(rand() % (static_cast<int>(window.getSize().x - this->shape.getGlobalBounds().width)-20))+10,
        static_cast<float>(rand() % (static_cast<int>(window.getSize().y - this->shape.getGlobalBounds().height)-20))+10
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