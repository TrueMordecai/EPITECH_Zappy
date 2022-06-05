#include "Population.hpp"

Population::Population()
{
    
}

Population::~Population()
{
    
}

void Population::parseCommand(std::vector<std::string> c)
{
    addPlayer(UP, {3, 6}, "Okay!", "Okay1");
}

Player *Population::getPlayerById(std::string id)
{
    for (unsigned int i = 0; i != getPlayers().size(); i++) {
        if (_players[i]->getId() == id)
            return (_players[i]);
    }
    return (nullptr);
}

std::vector<Player *> Population::getPlayerByPos(sf::Vector2i pos)
{
    std::vector<Player *> bfr;
    
    for (unsigned int i = 0; i != getPlayers().size(); i++) {
        if (_players[i]->getPosition() == pos)
            bfr.push_back(_players[i]);
    }
    return (bfr);
}

std::vector<Player *> Population::getPlayerByTeam(std::string team)
{
    std::vector<Player *> bfr;
    
    for (unsigned int i = 0; i != getPlayers().size(); i++) {
        if (_players[i]->getTeamName() == team)
            bfr.push_back(_players[i]);
    }
    return (bfr);
}




std::vector<Player*> Population::getPlayers()
{
    return _players;
}

void Population::addPlayer(e_orientation o, sf::Vector2i pos, std::string team, std::string id)
{
    Player *p = new Player(o, pos, team, id);
    _players.push_back(p);
}