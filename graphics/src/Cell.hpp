#ifndef __CELL_HPP_
#define __CELL_HPP_
#include <SFML/Graphics.hpp>
#include "mEntity.hpp"

class Cell
{
public:
    Cell(sf::Texture loadedTex, sf::Vector2i _pos);
    ~Cell();
    // Temp
    sf::RectangleShape &getShape();
    
    mEntity *getCell();
    sf::Vector2i getPosition();
    int food();
    int deraumere();
    int linemate();
    int sibur();
    int mendiane();
    int phiras();
    int thystame();
    std::vector<int> getAllItems(); // In a vector sort from low to high raraity, exclude food
    void addItem(char i);
    void addItems(char i, int q);
    void remItem(char i);
    void clearItem();

private:
    sf::Vector2i _position;
    sf::RectangleShape _cell;
    mEntity *_texture;
    
    int _food = 0;
    int _deraumere = 0;
    int _linemate = 0;
    int _sibur = 0;
    int _mendiane = 0;
    int _phiras = 0;
    int _thystame = 0;

};

#endif