#include "Player.hpp"

Player::Player()
{
    this->_head = new mEntity("assets/isaac.png", sf::IntRect(0, 0 , 32, 32), 100, 1);
    this->_body = new mEntity("assets/isaac.png", sf::IntRect(0, 32, 32, 16), 100, 9);
    _head->getSprite().setScale(sf::Vector2f(4, 4));
    _body->getSprite().setScale(sf::Vector2f(4, 4));
    _stage = 2;
    _orientation = e_orientation::DOWN;
}

Player::~Player()
{
    
}

int Player::getStage()
{
    return _stage;
}

void Player::setStage()
{
    
}

mEntity* Player::getHead()
{
    return _head;
}

mEntity* Player::getBody()
{
    return _body;
}

void Player::update()
{
    _head->update();
    _body->update();
}

e_orientation Player::getOrientation()
{
    return _orientation;
}

void Player::setOrientation(e_orientation o)
{
    _orientation = o;
}

