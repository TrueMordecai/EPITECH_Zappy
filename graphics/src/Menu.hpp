#include "mEntity.hpp"
#ifndef __MENU_HPP__
#define __MENU_HPP__
#include "SFML/Graphics.hpp"

class Menu
{

public:
    Menu();
    ~Menu();
    void drawMenu(sf::RenderWindow &w);
    void handleEvent(sf::Event e);
    bool tryConnect(void);
    std::string getPort();
    std::string getIps();
    bool getPlay();
    void setConnection(bool c);
    void drawCornerNetwork(sf::RenderWindow &w);
private:
    sf::Text _text;
    sf::Text _textIp;
    sf::Text _textPort;
    sf::Text _textConnected;
    sf::Font _font;
    sf::Font _font2;
    mEntity *_menuBg;
    mEntity *_title;
    sf::Vector2f _offset;
    std::string _ip;
    std::string _port;
    int _activeMenu = 0;
    int _menu0 = 0;
    int _menu1 = 0;
    int _menu2 = 0;
    bool _sense = false;
    bool _enlarge = false;
    bool _tryConnect = false; 
    bool _play = false;
    bool _connected = false;
};
#endif