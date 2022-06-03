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
    int f = 1;

    while (d.loop()) {
        p.update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            p.setOrientation(e_orientation::UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            p.setOrientation(e_orientation::LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            p.setOrientation(e_orientation::RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            p.setOrientation(e_orientation::DOWN);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            p.setStage(1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            p.setStage(2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            p.setStage(3);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            p.setStage(4);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            p.setStage(5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            p.setStage(6);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            p.setStage(7);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            p.setStage(8);
        d.moveCamera();
        d.drawGrid();
        d.drawPlayer(p);
        d.display();
        d.clear();
    }
    return (0);
}