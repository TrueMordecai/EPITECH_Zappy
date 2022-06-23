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

int Cell::food()
{
    return _food;
}

int Cell::linemate()
{
    return _linemate;
}

int Cell::deraumere()
{
    return _deraumere;
}

int Cell::sibur()
{
    return _sibur;
}

int Cell::mendiane()
{
    return _mendiane;
}

int Cell::phiras()
{
    return _phiras;
}

int Cell::thystame()
{
    return _thystame;
}

std::vector<int> Cell::getAllItems()
{
    return {_linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame};
}

void Cell::addItem(char i)
{
    if (i == 'l')
        _linemate++;
    if (i == 'd')
        _deraumere++;
    if (i == 's')
        _sibur++;
    if (i == 'm')
        _mendiane++;
    if (i == 'p')
        _phiras++;
    if (i == 't')
        _thystame++;
    if (i == 'f')
        _food++;
}

void Cell::addItems(char i, int q)
{
    if (i == 'l')
        _linemate += q;
    if (i == 'd')
        _deraumere += q;
    if (i == 's')
        _sibur += q;
    if (i == 'm')
        _mendiane += q;
    if (i == 'p')
        _phiras += q;
    if (i == 't')
        _thystame += q;
    if (i == 'f')
        _food += q;
}

void Cell::remItem(char i)
{
    std::cout << "Removing" << i << "On cell " << _position.x << "." << _position.y << "\n";
    if (i == 'l')
        _linemate -= 1;
    if (i == 'd')
        _deraumere -= 1;
    if (i == 's')
        _sibur -= 1;
    if (i == 'm')
        _mendiane -= 1;
    if (i == 'p')
        _phiras -= 1;
    if (i == 't')
        _thystame -= 1;
    if (i == 'f')
        _food -= 1;
}

void Cell::clearItem()
{
    _linemate = 0;
    _deraumere = 0;
    _sibur = 0;
    _mendiane = 0;
    _phiras = 0;
    _thystame = 0;
    _food = 0;
}
