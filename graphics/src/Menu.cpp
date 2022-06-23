#include "Menu.hpp"


Menu::Menu()
{
    _font.loadFromFile("./assets/hud/font2.ttf");
    _font2.loadFromFile("./assets/hud/font1.ttf");
    _text.setFillColor(sf::Color(54, 45, 45));
    _text.setCharacterSize(80);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
    _text.setFont(_font);
    
    _textIp.setFillColor(sf::Color(54, 45, 45));
    _textIp.setCharacterSize(70);
    _textIp.setOutlineThickness(0);
    _textIp.setOutlineColor(sf::Color::Black);
    _textIp.setFont(_font);

    _textPort.setFillColor(sf::Color(54, 45, 45));
    _textPort.setCharacterSize(100);
    _textPort.setOutlineThickness(0);
    _textPort.setOutlineColor(sf::Color::Black);
    _textPort.setFont(_font);

    _textConnected.setFillColor(sf::Color::Red);
    _textConnected.setCharacterSize(15);
    _textConnected.setOutlineThickness(1);
    _textConnected.setOutlineColor(sf::Color::Black);
    _textConnected.setString("Offline mode");
    _textConnected.setFont(_font2);
    _textConnected.setPosition(1920 - _textConnected.getLocalBounds().width - 20, 0);
    
    _menuBg = new mEntity("./assets/menu/menu.png", {0, 0, 480, 256});
    _menuBg->getSprite().setScale({8, 8});
    _title = new mEntity("./assets/menu/title.png", {0, 0, 256, 55});
    _title->getSprite().setScale({3, 3});
    _title->getSprite().setOrigin(256 / 2, 55 / 2);
    _text.setString("->");
    _offset = {0, 0};
    _ip = "localhost";
    _port = "88844";
}

Menu::~Menu()
{
    
}

void Menu::drawMenu(sf::RenderWindow &w)
{
    _menuBg->getSprite().setPosition(0, 0);
    _text.setPosition(0, 0);
    _title->getSprite().setPosition(960, 160);
    _textIp.setString(_ip);
    _textPort.setString(_port);
    _textIp.setPosition(1460, 1469); 
    _textPort.setPosition(1530, 1655);
    if (_ip.size() == 0 and _menu1 != 1)
        _ip = "localhost";
    float sc = _title->getSprite().getScale().x;
    if (_enlarge)
        _title->getSprite().scale(1.001, 1.001);
    else
        _title->getSprite().scale(0.999, 0.999);
    if (sc >= 3.2)
        _enlarge = false;
    if (sc <= 2.7)
        _enlarge = true;
    float ro = _title->getSprite().getRotation();
    if (!_sense)
        _title->getSprite().rotate((5.5 - ro) / 40);
    else
        _title->getSprite().rotate(-(ro / 40));
    if (ro >= 5 and ro <= 6)
        _sense = true;
    if (ro >= 0 and ro <= 1)
        _sense = false;

    if (_activeMenu == 0) { // Main
        _offset = {_offset.x + ((0 - _offset.x) / 15), _offset.y + ((0 - _offset.y) / 15)};
        _text.setString("->");
        _text.setPosition(650, 350);
        _text.move(-_menu0 * 10, _menu0 * 125); 
    }

    if (_activeMenu == 2) { // Rules
        _offset = {_offset.x + ((-1900 - _offset.x) / 15), _offset.y + ((-200 - _offset.y) / 15)};
        _text.setString("<-"); // Back
        _text.setPosition(2630, 200);
    }

    if (_activeMenu == 1) { // Settings
        _offset = {_offset.x + ((-500 - _offset.x) / 15), _offset.y + ((-1000 - _offset.y) / 15)};
        if (_menu1 == 0) { // Back
            _text.setString("<-");
            _text.setPosition(1200, 1340);
        }
        if (_menu1 == 1) { // ip
            _text.setString(">"); 
            _text.setPosition(1160, 1455);
        }
        if (_menu1 == 2) {  // Port
            _text.setString(">"); 
            _text.setPosition(1170, 1655);
        }
        if (_menu1 == 3) { // Try to connect
            _text.setString("->");
            _text.setPosition(1360, 1790);
        }
    }
    _text.move({_offset.x, _offset.y});
    _menuBg->getSprite().move(_offset);
    _title->getSprite().move(_offset);
    _textIp.move(_offset);
    _textPort.move(_offset);
    w.draw(_menuBg->getSprite());
    w.draw(_text);
    w.draw(_textPort);
    w.draw(_textIp);
    w.draw(_title->getSprite());
}

void Menu::handleEvent(sf::Event e)
{
    if (e.type == sf::Event::TextEntered and _activeMenu == 1) {
        if (!((static_cast<char>(e.text.unicode) >= '0' and static_cast<char>(e.text.unicode) <= '9') or static_cast<char>(e.text.unicode) == '.' or static_cast<char>(e.text.unicode) == 8))
            return;
        if (_menu1 == 1 and e.text.unicode == 8 and _ip.size() > 0) { // ip
            _ip.pop_back();
        }
        if (_menu1 == 2 and e.text.unicode == 8 and _port.size() > 0) // ip
            _port.pop_back();
        if (e.text.unicode == 8)
            return;
        if (_menu1 == 1 and _ip.size() < 15) { // ip
            _ip += static_cast<char>(e.text.unicode);
        }
        if (_menu1 == 2 and _port.size() <= 6) { // Port
            _port += static_cast<char>(e.text.unicode);
        }
    }

    if (e.key.code != sf::Keyboard::Up and e.key.code != sf::Keyboard::Down and e.key.code != sf::Keyboard::Enter)
        return;
    if (_activeMenu == 0) {
        if (e.key.code == sf::Keyboard::Up)
            _menu0--;
        if (e.key.code == sf::Keyboard::Down)
            _menu0++;
        if (_menu0 > 2)
            _menu0 = 0;
        if (_menu0 < 0)
            _menu0 = 2;
        if (e.key.code == sf::Keyboard::Enter and (_menu0 == 1 or _menu0 == 2)) {
            _activeMenu = _menu0;
        }
        if (e.key.code == sf::Keyboard::Enter and _menu0 == 0) {
            _play = true;
        }
        return;
    }

    if (_activeMenu == 1) { // Settings. 0 = back, 1 = ip, 2 = port, 3 = try to conect
        if (e.key.code == sf::Keyboard::Up)
            _menu1--;
        if (e.key.code == sf::Keyboard::Down)
            _menu1++;
        if (_menu1 > 3)
            _menu1 = 0;
        if (_menu1 < 0)
            _menu1 = 3;
        if (e.key.code == sf::Keyboard::Enter and _menu1 == 0)
            _activeMenu = 0;
        if (e.key.code == sf::Keyboard::Enter and _menu1 == 3)
            _tryConnect = true;
        return;
    }
    if (_activeMenu == 2) { // Rules
        if (e.key.code == sf::Keyboard::Enter)
            _activeMenu = 0;
        return;
    }
}

bool Menu::tryConnect(void)
{
    bool s = _tryConnect;
    _tryConnect = false;
    return s;
}

std::string Menu::getPort()
{
    return _port;
}

std::string Menu::getIps()
{
    return _ip;
}

bool Menu::getPlay()
{
    
    return _play;
}

void Menu::setConnection(bool c)
{
    if (c) {
        _textConnected.setFillColor(sf::Color::Green);
        _textConnected.setString("Online mode");
        _connected = true;
    } else {
        _textConnected.setFillColor(sf::Color::Red);
        _textConnected.setString("Offline mode");
        _connected = false;
    }
}

void Menu::drawCornerNetwork(sf::RenderWindow &w)
{
    w.draw(_textConnected);
}