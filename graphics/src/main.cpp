/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Main
*/

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "Drawer.hpp"
#include "Player.hpp"
#include <stdlib.h>
int main()
{
    Drawer d;
    Player p;    
    while (d.loop()) {
        p.update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            p.setOrientation(e_orientation::UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            p.setOrientation(e_orientation::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            p.setOrientation(e_orientation::RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            p.setOrientation(e_orientation::DOWN);
        d.drawPlayer(p);
        d.display();
        d.clear();
    }
    return (0);
}