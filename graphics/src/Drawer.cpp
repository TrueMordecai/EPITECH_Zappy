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

    for (int y = 0; y != _mapSize.x; y++) {
        for (int x = 0; x != _mapSize.y; x++) {
            Cell *ncell = new Cell({x, y});
            _cells.push_back(ncell);
        }        
    }
    _font.loadFromFile("assets/hud/font1.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(32);
    _text.setFillColor(sf::Color::Black);
    _text.setString("TEST");
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
    
    p.getBody()->getSprite().setPosition(sf::Vector2f(p.x() * 128, p.y() * 128 + 32));

    if (!((p.getPosition().x == p.getPositionGoal().x) and (p.getPosition().y == p.getPositionGoal().y)))
        movePlayer(p);

    p.getBody()->getSprite().move(_camOffset.x, _camOffset.y);
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
    if (p.getPositionGoal().x * 128 > p.getBody()->getSprite().getPosition().x) {
            p.setOrientation(RIGHT);
            p.addMovementOffset({float(128.0 / (60.0 * (7.0/f))), 0.0});
            p.getBody()->getSprite().move(p.getMovementOffset().x, 0);
        if (p.getBody()->getSprite().getPosition().x >= p.getPositionGoal().x * 128) {
            p.updatePosition();
            p.resetMovementOffset();
        }
        return;
    }
    if (p.getPositionGoal().x * 128 < p.getBody()->getSprite().getPosition().x) {
            p.setOrientation(LEFT);
            p.addMovementOffset({float(-(128.0 / (60.0 * (7.0/f)))), 0.0});
            p.getBody()->getSprite().move(p.getMovementOffset().x, 0);
        if (p.getBody()->getSprite().getPosition().x <= p.getPositionGoal().x * 128) {
            p.updatePosition();
            p.resetMovementOffset();
        }
        return;
    }
    if (p.getPositionGoal().y * 128 < p.getBody()->getSprite().getPosition().y) {
        p.setOrientation(UP);
        p.addMovementOffset({0.0, float(-(128.0 / (60.0 * (7.0/f))))});
        p.getBody()->getSprite().move(0, p.getMovementOffset().y);
        if (p.getBody()->getSprite().getPosition().y <= p.getPositionGoal().y * 128 + 32) {
            p.updatePosition();
            p.resetMovementOffset();
        }
        return;
    }
    if (p.getPositionGoal().y * 128 > p.getBody()->getSprite().getPosition().y) {
        p.setOrientation(DOWN);
        p.addMovementOffset({0.0, float((128.0 / (60.0 * (7.0/f))))});
        p.getBody()->getSprite().move(0, p.getMovementOffset().y);
        if (p.getBody()->getSprite().getPosition().y >= p.getPositionGoal().y * 128 + 32) {
            p.updatePosition();
            p.resetMovementOffset();
        }
    }
}

void Drawer::moveCamera()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _camOffset.y += 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _camOffset.x += 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _camOffset.x -= 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _camOffset.y -= 4;
}

void Drawer::drawInfo(Player &p)
{
    std::string s = "Camera offset : ";
    s += std::to_string(_camOffset.x);
    s += " / ";
    s += std::to_string(_camOffset.y);

    s += "\nPlayer Current Grid Position : ";
    s += std::to_string(p.x());
    s += " / ";
    s += std::to_string(p.y());
    
    s += "\nPlayer Goal Grid Position : ";
    s += std::to_string(p.getPositionGoal().x);
    s += " / ";
    s += std::to_string(p.getPositionGoal().y);

    s += "\nPlayer Body Position : ";
    s += std::to_string(p.getBody()->getSprite().getPosition().x);
    s += " / ";
    s += std::to_string(p.getBody()->getSprite().getPosition().y);

    s += "\nBuggy condition : ";
    s += std::to_string(p.getBody()->getSprite().getPosition().x);
    s += " <= ";
    s += std::to_string(p.getPositionGoal().x * 128 + _camOffset.x);

    s += "\nWorking condition : ";
    s += std::to_string(p.getBody()->getSprite().getPosition().x + _camOffset.x);
    s += " >= ";
    s += std::to_string(p.getPositionGoal().x * 128 + _camOffset.x);
    // p.getBody()->getSprite().getPosition().x + _camOffset.x >= p.getPositionGoal().x * 128 + _camOffset.x


    _text.setString(s);
    
    
    _window->draw(_text);
}

sf::RenderWindow &Drawer::getWindow()
{
    return *_window;
}

Cell Drawer::getCellFromClick()
{
    sf::Vector2i pos = sf::Mouse::getPosition(*_window);
    pos.x -= _camOffset.x;
    pos.y -= _camOffset.y;
    return (*_cells[(pos.x / 128) + ((pos.y / 128 * 20))]);
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
    (void)p;
    _window->draw(_stage3->getSprite());
}


void Drawer::drawGrid()
{
    for (long unsigned int i = 0; i != _cells.size(); i++) {
        _cells[i]->getShape().setPosition(sf::Vector2f(_cells[i]->getPosition().x * 128 + _camOffset.x, _cells[i]->getPosition().y * 128 + _camOffset.y));
        _window->draw(_cells[i]->getShape());
    }
}
