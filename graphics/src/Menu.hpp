#include "mEntity.hpp"
#ifndef __MENU_HPP__
#define __MENU_HPP__
#include "SFML/Graphics.hpp"

class Menu
{

public:
    Menu();
    ~Menu();
    void drawMenu(sf::RenderWindow &w);
    void handleEvent(sf::Event e);
private:
    sf::Text _text;
    sf::Font _font;
    sf::Vector2f _offset;
    int activeMenu = 0;
    int menu0 = 0;
    int menu1 = 0;
    int menu2 = 0;
};
#endif