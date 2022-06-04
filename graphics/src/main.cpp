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
#include "Hud.hpp"
#include <stdlib.h>



int main()
{
    Drawer d;
    Player p;
    Hud h;
    int f = 1;

    while (d.loop()) {
        p.update();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (p.getPosition() == d.getCellFromClick().getPosition()) {
                h.setState(Hud::HudState::SHOW);
            } else {
                h.setState(Hud::HudState::HIDE);
            }
        }
        d.moveCamera();
        d.drawGrid();
        d.drawPlayer(p);
        d.drawInfo(p);
        h.drawHud(d.getWindow(), p);
        d.display();
        d.clear();
    }
    return (0);
}