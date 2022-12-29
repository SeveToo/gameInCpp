#include <bits/stdc++.h>
#include "Player.h"

sf::Texture pl;
extern int keyEffect;

void Player::initVariables()
{
    this->movementSpeed = 5.f;
    this->hpMax = 10;
    this->hp = hpMax;
}

void Player::initShape()
{
    pl.loadFromFile("assets/player.png");
    this->shape.setSize(sf::Vector2f(50.f, 100.f));
    this->shape.setTexture(&pl);
    
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

// Accessors

const sf::RectangleShape & Player::getShape() const
{
    return this->shape;
}

const int & Player::getHp() const {
    return this->hp;
}

const int & Player::getHpMax() const {
    return this->hpMax;
}

// Functions

void Player::takeDamage(const int demage) {
    if (this->hp > 0)
        this->hp -= demage;

    if (this->hp < 0)
        this->hp = 0;
}

void Player::gainHealth(const int health) {
    if(this->hp < this->hpMax)
        this->hp += health;
    else
    this->hpMax += health;

    if (this->hpMax > this->hpMax)
        this->hpMax = this->hpMax;
}
int16_t move = 0;
void Player::updateInput()
{   
    // Keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        move = 0;
    // LEFT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move = 1;
    // RIGHT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move = 2;
    // UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move = 3;
    // DOWN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move = 4;
    
    if(move==1)this->shape.move(-this->movementSpeed, 0.f);
    if(move==2)this->shape.move(this->movementSpeed, 0.f);
    if(move==3)this->shape.move(0.f, -this->movementSpeed);
    if(move==4)this->shape.move(0.f, this->movementSpeed);
}

// void Player::updatePoints()
// {
//     std::cout<<"text";
// }

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    // Left
    if (this->shape.getGlobalBounds().left <= 0.f)
        if(keyEffect>0) this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width-1, this->shape.getGlobalBounds().top);
        else this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);

    // Right
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
        if(keyEffect>0) this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
        else this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width-1, this->shape.getGlobalBounds().top);

    // Top
    if (this->shape.getGlobalBounds().top <= 0.f)
        if(keyEffect>0) this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height-1);
        else this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);

    // Bottom
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
        if(keyEffect>0) this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
        else this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height-1);

}

void Player::update(const sf::RenderTarget* target)
{
    // Keyboard input
    this->updateInput();

   // Window bounds collision
    this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}