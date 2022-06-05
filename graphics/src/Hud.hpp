#ifndef __HUD_HPP_
#define __HUD_HPP_
#include "mEntity.hpp"
#include "SFML/Graphics.hpp"
#include "Player.hpp"

class Hud
{

public:
    enum HudState {
        HIDE = 0,
        SHOW
    };
    Hud();
    ~Hud();
    void showHud(Player &p);
    void hideHud();
    void drawHud(sf::RenderWindow &w, Player *p);
    mEntity *getHud();
    void setState(HudState state, std::string id);
    std::string getIdToDraw();
private:
    void moveHud(HudState state);
    std::string _idToShow;
    mEntity *_heart;
    mEntity *_hud;
    sf::Text _text;
    sf::Font _font1;
    sf::Font _font2;
    HudState _e_state;
    sf::Vector2f _offset;
};


#endif