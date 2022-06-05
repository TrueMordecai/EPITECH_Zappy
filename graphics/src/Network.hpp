#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

class Network
{
public:
    Network();
    ~Network();
    std::vector<std::string> manualCommand(sf::Event event);
    sf::Text getText();
private:
    std::string _buffer;
    sf::Text _text;
    sf::Font _font;
};

#endif