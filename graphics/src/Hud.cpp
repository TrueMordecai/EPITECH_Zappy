#include "Hud.hpp"
#include "mEntity.hpp"

Hud::Hud()
{
    _heart = new mEntity("./assets/hud/heart.png", {0, 0, 16, 14}, 100, 1, LEFT_TO_RIGHT, "full");
    _heart->addAnimationLoop("half", 1, 100, {16, 0, 16, 14});
    _hud = new mEntity("./assets/hud/hud.png", {0, 0, 204, 236});
    _font1.loadFromFile("./assets/hud/font1.ttf");
    _font2.loadFromFile("./assets/hud/font2.ttf");
    _hud->getSprite().setScale(4, 4);
    _hud->getSprite().setPosition(1920, 0);
    _text.setFont(_font2);
    _text.setCharacterSize(54);
    _text.setRotation(2);
    _text.setFillColor(sf::Color(54, 45, 45));
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
    _e_state = SHOW;
    _heart->getSprite().setScale(4, 4);
    _playerToShow = nullptr;
}

Hud::~Hud()
{
    
}

void Hud::showHud(Player &p)
{
    (void)p;
    //moveHud(_e_state);
}

void Hud::hideHud()
{
    _e_state = HIDE;
    //moveHud(_e_state);
}

void Hud::drawHud(sf::RenderWindow &w, std::vector<Player *> _teamates)
{
    if (_playerToShow == nullptr)
        _e_state = HIDE;
    moveHud(_e_state, sf::Mouse::getPosition(w));
    w.draw(_hud->getSprite());
    if (_playerToShow == nullptr)
        return;

    /// Draw X
    _text.setPosition(2610, 105);
    _text.move(_offset);
    _text.setString(std::to_string(_playerToShow->getPosition().x));
    w.draw(_text);

    /// Draw Y
    _text.setPosition(2610, 170);
    _text.move(_offset);
    _text.setString(std::to_string(_playerToShow->getPosition().y));
    w.draw(_text);
    
    /// Draw Team Name
    _text.setRotation(7);
    _text.setPosition(2480, 220);
    _text.move(_offset);
    _text.setString(_playerToShow->getTeamName());
    while (_text.getGlobalBounds().width > 220)
        _text.setCharacterSize(_text.getCharacterSize() - 1);
    w.draw(_text);
    _text.setCharacterSize(54);

    /// Draw Level
    _text.setPosition(2440, 350);
    _text.setCharacterSize(100);
    _text.move(_offset);
    _text.setFillColor(sf::Color(54 + 10 * _playerToShow->getStage(), 45, 45));
    _text.setString(std::to_string(_playerToShow->getStage()));
    w.draw(_text);
    _text.setCharacterSize(54);
    _text.setFillColor(sf::Color(54, 45, 45));

    /// Draw Friend
    _text.setPosition(2300, 550);
    _text.setCharacterSize(40);
    _text.setOutlineThickness(0);
    _text.move(_offset);
    for (int i = 0; i != _teamates.size(); i++) {
        std::string sbfr = "";
        sbfr += _teamates[i]->getId();
        sbfr += " lvl. ";
        sbfr += std::to_string(_teamates[i]->getStage());
        
        _text.move({0, 40});
        _text.setString(sbfr);
        w.draw(_text);
    }
    _text.setOutlineThickness(1);
    
    /// Draw Id
    _text.setRotation(7);
    _text.setPosition(2300, 815);
    _text.setCharacterSize(50);
    _text.move(_offset);
    _text.setString(_playerToShow->getId());
    while (_text.getGlobalBounds().width > 220)
        _text.setCharacterSize(_text.getCharacterSize() - 1);
    w.draw(_text);
    _text.setCharacterSize(54);

    /// Draw heart
    _heart->getSprite().setPosition(1950, 530);
    _heart->getSprite().move(_offset);
    for (int i = 0; i != 6; i++) {
        _heart->getSprite().move(64, 0);
        if (i == 3)
            _heart->getSprite().move(-160, 55);
        if (_playerToShow->getLife() >= i * 210 && _playerToShow->getLife() <= i * 210 + 105)
            _heart->changeAnimationLoop("half");
        else
            _heart->changeAnimationLoop("full");
        if (i * 210 > _playerToShow->getLife())
            return;
        _heart->display(w);
    }
}

mEntity* Hud::getHud()
{
    return _hud;
}

void Hud::setState(HudState state, std::string id)
{
    _idToShow = id;
    _e_state = state;
}

std::string Hud::getIdToDraw()
{
    if (_playerToShow)
        return _playerToShow->getId();
    return "";
}

void Hud::setPlayerToDraw(Player *p)
{
    _playerToShow = p;
    if (!p) {
        std::cout << "p == NULL\n";
        _e_state = HIDE;
    } else {
        std::cout << "p == SHOW\n";
        _e_state = SHOW;
    }
}

void Hud::moveHud(HudState state, sf::Vector2i max)
{
    _hud->getSprite().setPosition(1920, 0); // Set paper at initial place
    if (state == SHOW) // if paper should be shown, increase offset
        _offset += {-45, 0};
    if (state == HIDE) // else decrease offset
        _offset += {25, 0};
    
    _hud->getSprite().move(_offset); // Move the paper based on offset    

    if (_hud->getSprite().getPosition().x < 1920 - _hud->getSprite().getLocalBounds().width * 4) { // If paper go to far left
        _hud->getSprite().setPosition(1920 - _hud->getSprite().getLocalBounds().width * 4, 0);
        _offset = {-_hud->getSprite().getLocalBounds().width * 4, 0}; // Max left offset
    }
    if (_hud->getSprite().getPosition().x < max.x) { // If paper go to far left
        _hud->getSprite().setPosition(max.x, 0);
        _offset = {(max.x - 1920), 0}; // Max left offset
        return;
    }
    if (_hud->getSprite().getPosition().x > 1920){ // If paper go to far right
        _hud->getSprite().setPosition(1920, 0);
        _offset = {0, 0}; // Max right offset
    }
}

