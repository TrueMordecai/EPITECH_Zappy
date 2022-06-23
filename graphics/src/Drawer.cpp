#include "Drawer.hpp"

Drawer::Drawer(sf::Vector2i msz)
{
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1024), "MyWindow");
    _window->setFramerateLimit(60);
    
    _rect.setPosition(-1, -1);
    _rect.setSize(sf::Vector2f(128 * 3, 128));
    _rect.setFillColor(sf::Color(0, 0, 0, 100));
    _rect.setOutlineColor(sf::Color::Black);
    _rect.setOutlineThickness(1);

    _items = new mEntity("assets/items.png", sf::IntRect(32 * 0, 0, 32, 32), 100, 2, LEFT_TO_RIGHT, "stage1");
    _items->addAnimationLoop("stage2", 2, 100, sf::IntRect(32 * 1, 0, 32, 32));
    _items->addAnimationLoop("stage3", 2, 100, sf::IntRect(32 * 2, 0, 32, 32));
    _items->addAnimationLoop("stage4", 2, 100, sf::IntRect(32 * 3, 0, 32, 32));
    _items->addAnimationLoop("stage5", 2, 100, sf::IntRect(32 * 4, 0, 32, 32));
    _items->addAnimationLoop("stage6", 2, 100, sf::IntRect(32 * 5, 0, 32, 32));
    _items->addAnimationLoop("food", 2, 100, sf::IntRect(32 * 6, 0, 32, 32));
//    _items->getSprite().scale(1.7, 1.7);


    _stage2 = new mEntity("assets/stage2.png", sf::IntRect(0, 0, 32, 26), 300, 2, LEFT_TO_RIGHT, "DOWN");
    _stage2->addAnimationLoop("RIGHT", 2, 300, sf::IntRect(64, 0, 32, 26));
    _stage2->addAnimationLoop("UP", 2, 300, sf::IntRect(128, 0, 32, 26));
    _stage2->addAnimationLoop("LEFT", 2, 300, sf::IntRect(192, 0, 32, 26));

    _stage3 = new mEntity("assets/stage3.png", sf::IntRect(0, 0, 32, 32), 300, 2, LEFT_TO_RIGHT, "DOWN");
    _stage3->addAnimationLoop("RIGHT", 2, 300, sf::IntRect(64, 0, 32, 32));
    _stage3->addAnimationLoop("UP", 2, 300, sf::IntRect(128, 0, 32, 32));
    _stage3->addAnimationLoop("LEFT", 2, 300, sf::IntRect(192, 0, 32, 32));

    _stage2->getSprite().setScale(sf::Vector2f(4, 4));
    _stage3->getSprite().setScale(sf::Vector2f(4, 4));
    _mapSize = msz;
    _camOffset = {0, 0};

    _font.loadFromFile("assets/hud/font1.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(32);
    _text.setFillColor(sf::Color::Black);
    _text.setString("TEST");

    _textInfo.setFont(_font);
    _textInfo.setCharacterSize(30);
    _textInfo.setFillColor(sf::Color::Black);
}

Drawer::~Drawer()
{
}

void Drawer::drawPlayer(Player &p)
{        
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
    
    p.getAccesories()->getSprite().setPosition(p.getBody()->getSprite().getPosition()); 
    if (p.getCharacter() == C_JUDAS)
        p.getAccesories()->getSprite().move({0, -110}); 
    if (p.getCharacter() == C_CAIN)
        p.getAccesories()->getSprite().move({0, -90}); 
    if (p.getCharacter() == C_SAMSON)
        p.getAccesories()->getSprite().move({0, -82}); 
    if (p.getCharacter() != C_ISAAC)
        _window->draw(p.getAccesories()->getSprite());

}

void Drawer::drawAllPlayer(std::vector<Player *> pop)
{
    for (unsigned int i = 0; i != pop.size(); i++) {
        pop[i]->update();            
        drawPlayer(*pop[i]);
    }
}

void Drawer::display()
{
    _window->display();
    clear();
}

void Drawer::clear()
{
    _window->clear(sf::Color::Blue);
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

void Drawer::moveCamera(Player *p)
{    
    if (!(_mapSize.x > 15 && _mapSize.y > 8))
        return;
    if (!p) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _camOffset.y += 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _camOffset.x += 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _camOffset.x -= 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _camOffset.y -= 4;
    } else {
        _camOffset.x = 896 - 128 * p->getPosition().x - p->getMovementOffset().x;
        _camOffset.y = 512 - 128 * p->getPosition().y - p->getMovementOffset().y;
    }
    if (_camOffset.x > 0)
        _camOffset.x = 0;
    if (_camOffset.y > 0)
        _camOffset.y = 0;
    if (_camOffset.x < -(128 * _mapSize.x - 1920))
      _camOffset.x = -(128 * _mapSize.x - 1920);
    if (_camOffset.y < -(128 * _mapSize.y - 1080))
        _camOffset.y = -(128 * _mapSize.y - 1080);

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
    int s = ((pos.x / 128) + ((pos.y / 128 * _mapSize.y)));
    if (s < 0 or s > _cells.size() - 1)
        return (*_cells[0]);
    return (*_cells[(pos.y / 128) + ((pos.x / 128 * _mapSize.y))]);
}

bool Drawer::showMenu()
{
    return this->_isMenu;
}

void Drawer::setShowMenu(bool v)
{
    this->_isMenu = v;
}

void Drawer::createMap(sf::Vector2i a)
{
    if (_mapReady)
        return;
    sf::Texture temp;
    _mapSize = a;
    temp.loadFromFile("assets/tileset.png");
    for (int x = 0; x != a.x; x++) {
        for (int y = 0; y != a.y; y++) {
            Cell *ncell = new Cell(temp, {x, y});
            _cells.push_back(ncell);
        }        
    }
    _mapReady = true;
}

void Drawer::drawCellInfos(Cell c)
{
    _window->draw(_rect);
    _textInfo.setPosition(5, 5);   
    _textInfo.setCharacterSize(30);
    std::string bfr = "Cell #";
    bfr += std::to_string(c.getPosition().x + c.getPosition().y * _mapSize.y);
    bfr += "\nx : ";
    bfr += std::to_string(c.getPosition().x);
    bfr += ", y :";
    bfr += std::to_string(c.getPosition().y);
    _textInfo.setString(bfr);
    _window->draw(_textInfo);

    std::vector<int> items = c.getAllItems();
    _textInfo.setPosition(0, 85);
    _items->getSprite().setPosition(12, 85);
    _textInfo.setCharacterSize(20);
    for (int i = 0; i != items.size(); i++) {
        if (items[i] == 0)
            continue;
        _textInfo.setString(std::to_string(items[i])+ "-");
        _items->changeAnimationLoop("stage" + std::to_string(i + 1));
        _window->draw(_textInfo);
        _window->draw(_items->getSprite());
        _items->getSprite().move(54, 0);
        _textInfo.move(54, 0);
    }
    if (c.food() == 0)
        return;
    _textInfo.setString(std::to_string(c.food())+ "-");
    _window->draw(_textInfo);
    _items->changeAnimationLoop("food");
    _window->draw(_items->getSprite());    
}

void Drawer::parseMapCommand(std::vector<std::string> v)
{
    
    if (v.size() < 1)
        return;
    if (v[0] != "map" and v[0] != "l" and v[0] != "s" and v[0] != "m" and v[0] != "p" and v[0] != "t" and v[0] != "f")
        return;
    if (v[0].size() == 1 and v.size() >= 3) { // "$i $q $x $y" -> $item quatity posX posY -> Used for save some byte on protocol
        int x = int(v[2][0] - 'a');
        int y = int(v[3][0] - 'a');
        _cells[y + x * _mapSize.x]->addItems(v[0][0], std::atoi(v[1].c_str()));
        return;
    }
    if (v[1] == "spawn" and v.size() == 5) {// map spawn $i $x $y -> map spawn item posX posY
        int x = std::atoi(v[3].c_str());
        int y = std::atoi(v[4].c_str());
        _cells[y + x * _mapSize.x]->addItem(v[2].c_str()[0]);
    }
    if (v[1] == "rem" and v.size() == 5) { // map rem $i $x $y -> map spawn item posX posY
        int x = std::atoi(v[3].c_str());
        int y = std::atoi(v[4].c_str());
        _cells[y + x * _mapSize.x]->remItem(v[2].c_str()[0]);    
    }
}

bool Drawer::isMapReady()
{
    return _mapReady;
}

void Drawer::drawStage2(Player &p)
{
    _stage2->getSprite().setPosition(p.getHead()->getSprite().getPosition());
    _stage2->update();
    _stage2->synchronize(*p.getHead());
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
    _window->draw(_textInfo);
}


void Drawer::drawGrid()
{
    for (long unsigned int i = 0; i != _cells.size(); i++) {
        _cells[i]->getCell()->getSprite().setPosition(sf::Vector2f(_cells[i]->getPosition().x * 128 + _camOffset.x, _cells[i]->getPosition().y * 128 + _camOffset.y));
        _window->draw(_cells[i]->getCell()->getSprite());
        if (_cells[i]->food() >= 1) {
            _items->changeAnimationLoop("food");
            _items->getSprite().setPosition(_cells[i]->getCell()->getSprite().getPosition());
            _window->draw(_items->getSprite());
        }
    }
}
