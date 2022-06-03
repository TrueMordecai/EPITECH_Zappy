#include "Cell.hpp"

Cell::Cell(sf::Vector2i pos)
{
    _position = pos;
    _cell.setSize(sf::Vector2f(128, 128));
    _cell.setFillColor(sf::Color::Cyan);
    _cell.setOutlineColor(sf::Color::Black);
    _cell.setOutlineThickness(1);
}

Cell::~Cell()
{
    
}

sf::RectangleShape &Cell::getShape()
{
    return _cell;   
}

sf::Vector2i Cell::getPosition()
{
    return _position;
}
