#ifndef __CELL_HPP_
#define __CELL_HPP_
#include "SFML/Graphics.hpp"

class Cell
{
public:
    Cell(sf::Vector2i _pos);
    ~Cell();
    // Temp
    sf::RectangleShape &getShape();
    sf::Vector2i getPosition();
private:
    sf::Vector2i _position;
    
    // Temp too
    sf::RectangleShape _cell;
};

#endif