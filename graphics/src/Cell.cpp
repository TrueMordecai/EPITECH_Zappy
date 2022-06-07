#include "Cell.hpp"

Cell::Cell(sf::Texture t, sf::Vector2i pos)
{
    _position = pos;
    _cell.setSize(sf::Vector2f(128, 128));
    _cell.setFillColor(sf::Color::Cyan);
    _cell.setOutlineColor(sf::Color::Black);
    _cell.setOutlineThickness(1);

    
    _texture = new mEntity(t, sf::IntRect((pos.x % 5) * 64, (pos.y % 5) * 64, 64, 64));
    _texture->getSprite().setScale(2, 2);
}

Cell::~Cell()
{
    
}

sf::RectangleShape &Cell::getShape()
{
    return _cell;   
}

mEntity* Cell::getCell()
{
    return _texture;
}

sf::Vector2i Cell::getPosition()
{
    return _position;
}
