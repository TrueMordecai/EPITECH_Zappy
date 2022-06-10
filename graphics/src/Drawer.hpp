#include "Player.hpp"
#include "Cell.hpp"


#ifndef __DRAWER_HPP__
#define __DRAWER_HPP_

class Drawer
{
public:
    Drawer(sf::Vector2i mapSize);
    ~Drawer();
    void drawPlayer(Player &p);
    void drawAllPlayer(std::vector<Player *> pop);
    void drawGrid();
    void display();
    void clear();
    bool loop();
    void movePlayer(Player &p);
    void moveCamera(Player *p);
    void drawInfo(Player &p); /// Debug olny
    sf::RenderWindow &getWindow();
    Cell getCellFromClick();
private:
    void drawStage2(Player &p);
    void drawStage3(Player &p);


    sf::RenderWindow *_window;
    mEntity *_stage2;
    mEntity *_stage3;
    sf::RectangleShape _cell;
    int f = 10;
    sf::Vector2i _mapSize;
    sf::Vector2f _camOffset;
    std::vector<Cell*> _cells;
    sf::Text _text;
    sf::Font _font;
};
#endif