#include "Drawer.hpp"


#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

Drawer::Drawer(/* args */)
{
    _window = new sf::RenderWindow(sf::VideoMode(400, 400), "MyWindow");
    
    
    _stage2 = new mEntity("assets/stage2.png", sf::IntRect(0, 0, 32, 26), 100, 1, LEFT_TO_RIGHT, "DOWN");
    _stage2->addAnimationLoop("RIGHT", 1, 100, sf::IntRect(64, 0, 32, 26));
    _stage2->addAnimationLoop("UP", 1, 100, sf::IntRect(128, 0, 32, 26));
    _stage2->addAnimationLoop("LEFT", 1, 100, sf::IntRect(192, 0, 32, 26));


    _normal = new mEntity("assets/isaac.png", sf::IntRect(0, 0 , 32, 32), 100, 1, LEFT_TO_RIGHT, "DOWN");
    _normal->addAnimationLoop("RIGHT", 1, 100, sf::IntRect(64, 0, 32, 32));
    _normal->addAnimationLoop("UP", 1, 100, sf::IntRect(128, 0, 32, 32));
    _normal->addAnimationLoop("LEFT", 1, 100, sf::IntRect(192, 0, 32, 32));
    _black = new mEntity("assets/blackbody.png", sf::IntRect(0, 32, 32, 16), 100, 9);


    _black->getSprite().setScale(sf::Vector2f(4, 4));
    _normal->getSprite().setScale(sf::Vector2f(4, 4));
    _stage2->getSprite().setScale(sf::Vector2f(4, 4));
}

Drawer::~Drawer()
{
    
}

void Drawer::drawPlayer(Player &p)
{    
    
    if (p.getStage() > 5) {
        drawBody(p, _black);
        drawHead(p, _black);
    } else {
        drawBody(p, _normal);
        drawHead(p, _normal);
    }
}

void Drawer::display()
{
    _window->display();
}

void Drawer::clear()
{
    _window->clear(sf::Color::White);
}

bool Drawer::loop()
{
    return !sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

void Drawer::drawStage2(Player &p, mEntity *curHead)
{
    
    _stage2->getSprite().setPosition(curHead->getSprite().getPosition());
    if (p.getOrientation() == e_orientation::DOWN) {
        _stage2->getSprite().move(0, -24);
        _window->draw(curHead->getSprite());   
        _stage2->changeAnimationLoop("DOWN");
    }
    if (p.getOrientation() == e_orientation::LEFT) {
        _stage2->getSprite().move(0, -40);
        _stage2->changeAnimationLoop("LEFT");
        _window->draw(curHead->getSprite());   
    }
    if (p.getOrientation() == e_orientation::RIGHT) {
        _stage2->getSprite().move(0, -32);
        _window->draw(curHead->getSprite());   
        _stage2->changeAnimationLoop("RIGHT");
    }
    if (p.getOrientation() == e_orientation::UP) {
        _stage2->getSprite().move(0, -40);
        _window->draw(curHead->getSprite());   
        _stage2->changeAnimationLoop("UP");
    }
    _window->draw(_stage2->getSprite());
}

void Drawer::drawStage3(Player &p, mEntity *curHead)
{
    
}

void Drawer::drawStage4(Player &p, mEntity *curHead)
{
    
}

void Drawer::drawStage5(Player &p, mEntity *curHead)
{
    
}

void Drawer::drawStage6(Player &p, mEntity *curHead)
{
    
}

void Drawer::drawStage7(Player &p, mEntity *curHead)
{
    
}

void Drawer::drawStage8(Player &p, mEntity *curHead)
{
    
}

void Drawer::drawHead(Player &p, mEntity *head)
{
    if (p.getOrientation() == e_orientation::DOWN)
        head->changeAnimationLoop("DOWN");
    if (p.getOrientation() == e_orientation::LEFT)
        head->changeAnimationLoop("LEFT");
    if (p.getOrientation() == e_orientation::RIGHT)
        head->changeAnimationLoop("RIGHT");
    if (p.getOrientation() == e_orientation::UP)
        head->changeAnimationLoop("UP");
    if (p.getStage() == 1)
        drawStage2(p, head);

    if (p.getStage() == 2)
        drawStage2(p, head);
    
    if (p.getStage() == 3)
        drawStage3(p, head);
    
    if (p.getStage() == 4)
        drawStage4(p, head);
    
    if (p.getStage() == 5)
        drawStage5(p, head);
    
    if (p.getStage() == 6)
        drawStage6(p, head);
    
    if (p.getStage() == 7)
        drawStage7(p, head);
    
    if (p.getStage() == 8)
        drawStage8(p, head);
}

void Drawer::drawBody(Player &p, mEntity *body)
{
    p.getBody()->getSprite().setPosition(sf::Vector2f(body->getSprite().getPosition()));
    p.getBody()->getSprite().move(sf::Vector2f(0, 80));
    _window->draw(p.getBody()->getSprite());
}
#endif