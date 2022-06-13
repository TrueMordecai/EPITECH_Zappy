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
    void drawHud(sf::RenderWindow &w, std::vector<Player *> _teamates);
    mEntity *getHud();
    void setState(HudState state, std::string id);
    std::string getIdToDraw();
    void setPlayerToDraw(Player *p);
private:
    void moveHud(HudState state);
    std::string _idToShow;
    Player *_playerToShow;
    mEntity *_heart;
    mEntity *_hud;
    sf::Text _text;
    sf::Font _font1;
    sf::Font _font2;
    HudState _e_state;
    sf::Vector2f _offset;
};
#endif