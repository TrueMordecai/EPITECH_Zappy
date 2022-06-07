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
private:
    sf::Vector2i _position;
    
    // Temp too
    sf::RectangleShape _cell;
    mEntity *_texture;
};

#endif