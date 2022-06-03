#include "Drawer.hpp"

Drawer::Drawer(/* args */)
{
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "MyWindow");
    _window->setFramerateLimit(60);
    _cell.setSize(sf::Vector2f(128, 128));
    _cell.setFillColor(sf::Color::Cyan);
    _cell.setOutlineColor(sf::Color::Black);
    _cell.setOutlineThickness(1);

    _stage2 = new mEntity("assets/stage2.png", sf::IntRect(0, 0, 32, 26), 100, 1, LEFT_TO_RIGHT, "DOWN");
    _stage2->addAnimationLoop("RIGHT", 1, 100, sf::IntRect(64, 0, 32, 26));
    _stage2->addAnimationLoop("UP", 1, 100, sf::IntRect(128, 0, 32, 26));
    _stage2->addAnimationLoop("LEFT", 1, 100, sf::IntRect(192, 0, 32, 26));

    _stage3 = new mEntity("assets/stage3.png", sf::IntRect(0, 0, 32, 32), 100, 9, LEFT_TO_RIGHT, "DOWN");
    _stage3->addAnimationLoop("RIGHT", 1, 100, sf::IntRect(64, 0, 32, 32));
    _stage3->addAnimationLoop("UP", 1, 100, sf::IntRect(128, 0, 32, 32));
    _stage3->addAnimationLoop("LEFT", 1, 100, sf::IntRect(192, 0, 32, 32));

    _stage2->getSprite().setScale(sf::Vector2f(4, 4));
    _stage3->getSprite().setScale(sf::Vector2f(4, 4));
    _mapSize = {20, 20};
    _camOffset = {0, 0};

    for (int x = 0; x != _mapSize.x; x++) {
        for (int y = 0; y != _mapSize.y; y++) {
            std::cout << "New one!" << x << "/" << y <<"\n";
            Cell *ncell = new Cell({x, y});
            _cells.push_back(ncell);
        }        
    }
}

Drawer::~Drawer()
{
    
}

void Drawer::drawPlayer(Player &p)
{        
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
//        p.addMovementOffset({-1, 0});
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
//        p.addMovementOffset({1, 0});
    
    p.getBody()->getSprite().setPosition(sf::Vector2f(p.x() * 128 + _camOffset.x, p.y() * 128 + 32 + _camOffset.y));

    if (!((p.getPosition().x == p.getPositionGoal().x) and (p.getPosition().y == p.getPositionGoal().y)))
        movePlayer(p);

    int diff = (p.getHead()->getSprite().getGlobalBounds().width - p.getBody()->getSprite().getGlobalBounds().width) / 2;
    p.getHead()->getSprite().setPosition(sf::Vector2f(p.getBody()->getSprite().getPosition().x - diff,
                                                      p.getBody()->getSprite().getPosition().y - (p.getHead()->getSprite().getGlobalBounds().height) * 0.79));
        
    _window->draw(p.getBody()->getSprite());
    if (p.getStage() == 2)
        drawStage2(p);
    if (p.getStage() == 3)
        drawStage3(p);
    
    _window->draw(p.getHead()->getSprite());
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

void Drawer::movePlayer(Player &p)
{
    if (p.getPositionGoal().x * 128 + _camOffset.x > p.getBody()->getSprite().getPosition().x + _camOffset.x) {
            p.addMovementOffset({128.0 / (60.0 * (7.0/f)), 0});
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                p.getBody()->getSprite().move({-1, 0});
            p.getBody()->getSprite().move(p.getMovementOffset().x, p.getMovementOffset().y);
        if (p.getBody()->getSprite().getPosition().x + _camOffset.x >= p.getPositionGoal().x * 128 + _camOffset.x) {
            std::cout << "IDLE!\n";
            p.updatePosition();
            p.resetMovementOffset();
        }
    }
}

void Drawer::moveCamera()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _camOffset.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _camOffset.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _camOffset.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _camOffset.y += 1;
}

void Drawer::drawStage2(Player &p)
{
    _stage2->getSprite().setPosition(p.getHead()->getSprite().getPosition());
    if (p.getOrientation() == e_orientation::DOWN) {
        _stage2->changeAnimationLoop("DOWN");
        _stage2->getSprite().move(0, -24);
    }
    if (p.getOrientation() == e_orientation::LEFT) {
        _stage2->changeAnimationLoop("LEFT");
        _stage2->getSprite().move(0, -40);
    }
    if (p.getOrientation() == e_orientation::RIGHT) {
        _stage2->changeAnimationLoop("RIGHT");
        _stage2->getSprite().move(0, -32);
    }
    if (p.getOrientation() == e_orientation::UP) {
        _stage2->changeAnimationLoop("UP");
        _stage2->getSprite().move(0, -40);
    }
    _window->draw(_stage2->getSprite());
}

void Drawer::drawStage3(Player &p)
{
    _window->draw(_stage3->getSprite());
}


void Drawer::drawGrid()
{
    for (int i = 0; i != _cells.size(); i++) {
        _cells[i]->getShape().setPosition(sf::Vector2f(_cells[i]->getPosition().x * 128 + _camOffset.x, _cells[i]->getPosition().y * 128 + _camOffset.y));
        _window->draw(_cells[i]->getShape());
    }
    
    //for (int x = 0; x != _mapSize.x; x++) {
    //    for (int y = 0; y != _mapSize.y; y++) {
    //        _cell.setPosition(sf::Vector2f(x * _cell.getSize().x + _camOffset.x, y * _cell.getSize().y + _camOffset.y));
    //        _window->draw(_cell);
    //    }        
    //}
}
