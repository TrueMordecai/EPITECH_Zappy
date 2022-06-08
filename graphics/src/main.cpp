/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Main
*/

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "Drawer.hpp"
#include "Population.hpp"
#include "Hud.hpp"
#include "Network.hpp"
#include <stdlib.h>



int main()
{
    Drawer d;
    Hud h;
    Network n;
    sf::Event event;
    std::vector<std::string> bfr;
    Population pop;
    while (d.loop()) {
        bfr.clear();
        while (d.getWindow().pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::TextEntered): 
                    bfr = n.manualCommand(event);
                    break;
                case (sf::Event::KeyReleased):
                    n.manualCommand(event);
                    break;
                default:
                    break;
            }
        }
        if (bfr.size() > 0) {
            if (bfr[0] == "player") {
                pop.parseCommand(bfr);
            }
        }
        d.moveCamera(pop.getPlayerById(h.getIdToDraw()));
        d.drawGrid();
        for (unsigned int i = 0; i != pop.getPlayers().size(); i++) {
            pop.getPlayers()[i]->update();            
            d.drawPlayer(*pop.getPlayers()[i]);
        }
        for (unsigned int i = 0; i != pop.getPlayers().size(); i++) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (pop.getPlayers()[i]->getPosition() == d.getCellFromClick().getPosition()) {
                    h.setState(Hud::HudState::SHOW, pop.getPlayers()[i]->getId());
                    break;
                } else {
                    h.setState(Hud::HudState::HIDE, "");
                }
            }
        }

        h.drawHud(d.getWindow(), pop.getPlayerById(h.getIdToDraw()));
        d.getWindow().draw(n.getText());
        d.display();
        d.clear();
    }
    return (0);
}