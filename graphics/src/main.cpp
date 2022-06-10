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



int main(int ac, char **av)
{
    Hud h;
    Network n(av[1], std::atoi(av[2]));
    sf::Event event;
    std::vector<std::string> bfr;
    Population pop;
    std::vector<std::vector<std::string>> sbfr;

    while (1) {
        sbfr = n.serverCommand();
        
        if (sbfr.size() >= 1 && sbfr[0].size() == 3) {
            if (sbfr[0][0] == "SIZE") {
                std::cout << "Breaking !\n";
                break;
            }
        }
    }
    sf::Vector2i s  = {std::atoi(sbfr[0][1].c_str()), std::atoi(sbfr[0][2].c_str())};
    Drawer d(s);
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
                case (sf::Event::MouseButtonReleased):
                    h.setPlayerToDraw(pop.getPlayerByPos(d.getCellFromClick().getPosition())[0]);
                    break;
                default:
                    break;
            }
        }
        std::vector<std::vector<std::string>> servbfr = n.serverCommand();
        if (servbfr.size() >= 1) {
            std::cout << "Serv bfr is readable\n";
            pop.parseCommand(servbfr[0]);
        }
        pop.parseCommand(bfr);
        d.moveCamera(pop.getPlayerById(h.getIdToDraw()));
        d.drawGrid();
        d.drawAllPlayer(pop.getPlayers());
        h.drawHud(d.getWindow());
        d.getWindow().draw(n.getText());
        d.display();
    }
    return (0);
}