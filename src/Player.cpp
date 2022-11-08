#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 5.f;
}

void Player::initShape()
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShape();
}

Player::~Player()
{
}

void Player::updateInput()
{
    

    // Keyboard input
    // LEFT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->shape.move(-this->movementSpeed, 0.f);
    // RIGHT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->shape.move(this->movementSpeed, 0.f);
    // UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->shape.move(0.f, -this->movementSpeed);
    // DOWN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->shape.move(0.f, this->movementSpeed);
}

void Player::update(sf::RenderTarget* target)
{
   // Window bounds collision
    

   this->updateInput();
}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}