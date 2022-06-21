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
#include "Menu.hpp"

int main(int ac, char **av)
{
    Hud h;
    Network n;
    if (ac < 2)
        n.setInfo("localhost", 88860);
    else 
        n.setInfo(av[1], std::atoi(av[2]));
    sf::Event event;
    std::vector<std::string> bfr;
    Population pop;
    std::vector<std::vector<std::string>> sbfr;
    Menu m;
    Drawer d({20, 20});

    while (d.loop()) {
        bfr.clear();
        while (d.getWindow().pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::TextEntered): 
                    bfr = n.manualCommand(event);
                    m.handleEvent(event);
                    break;
                case (sf::Event::KeyReleased):
                    n.manualCommand(event);                    
                    m.handleEvent(event);
                    break;
                case (sf::Event::MouseButtonReleased):
                    if (d.showMenu() == false)
                        h.setPlayerToDraw(pop.getPlayerByPos(d.getCellFromClick().getPosition())[0]);
                    break;
                default:
                    break;
            }
        }
        if (m.tryConnect()) { // When player released the enter key on "try connection"
            std::cout << "Trying to connect" << "\n";
            n.connect(m.getIps(), std::atoi(m.getPort().c_str()));
        }
        if (n.getMapSize().x != 0)
            m.setConnection(true);            
        else
            m.setConnection(false);
        if (d.showMenu() and m.getPlay()) { // When map size is received in the network 
            if (n.getMapSize().x != 0)
                d.createMap(n.getMapSize());
            else
                d.createMap({20, 20});
            d.setShowMenu(false);
        }
        std::vector<std::vector<std::string>> servbfr = n.serverCommand();
        if (servbfr.size() >= 1) {
            for (auto c : servbfr)
                pop.parseCommand(c);
        }
        if (d.showMenu()) {
            m.drawMenu(d.getWindow());
        } else {
            d.moveCamera(pop.getPlayerById(h.getIdToDraw()));
            d.drawGrid();
            d.drawAllPlayer(pop.getPlayers());
            h.drawHud(d.getWindow(), pop.getPlayerByTeammateId(h.getIdToDraw()));
            d.getWindow().draw(n.getText());
        }
        m.drawCornerNetwork(d.getWindow());
        d.display();
    }
    return (0);
}