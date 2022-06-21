#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>
#include <SFML/Network.hpp>
#include <cstring>

class Network
{
public:
    Network();
    ~Network();
    std::vector<std::string> manualCommand(sf::Event event);
    std::vector<std::vector<std::string>> serverCommand();
    sf::Text getText();
    void connect(std::string ip, int port);
    void connect(); // Connect with saved information
    sf::Vector2i getMapSize(void);
    void setInfo(std::string ip, int port);

private:
    std::string _ip;
    int _port;
    sf::TcpSocket _socket;
    bool isConnected;
    std::string _buffer;
    sf::Text _text;
    sf::Font _font;
    std::vector<std::string> _history;
    std::vector<std::string> _preload;
    int _historyIndex = -1;
    sf::Vector2i _msz = {0, 0};
};
#endif