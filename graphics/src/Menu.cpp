#include "Menu.hpp"


Menu::Menu()
{
    _font.loadFromFile("./assets/hud/font2.ttf");
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(30);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
    _text.setPosition(50, 900);
    _text.setFont(_font);
}

Menu::~Menu()
{
    
}

void Menu::drawMenu(sf::RenderWindow &w)
{
    w.clear(sf::Color::White); // Temp
    _text.setString("TESTING");
    
    w.draw(_text);
}

void Menu::handleEvent(sf::Event e)
{
    if (e.key.code != sf::Keyboard::Up or e.key.code != sf::Keyboard::Down)
        return;
    if (activeMenu == 0) {
        if (e.key.code == sf::Keyboard::Up)
            menu0++;
        if (e.key.code == sf::Keyboard::Down)
            menu0--;
        if (menu0 > 2)
            menu0 = 0;
        if (menu0 < 0)
            menu0 = 2;
        

    }
}
