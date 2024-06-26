#ifndef __POPULATION_HPP_
#define __POPULATION_HPP_
#include "Player.hpp"

class Population
{
public:
    Population();
    ~Population();
    void parseCommand(std::vector<std::string> c);
    std::vector<Player*> getPlayers();
    Player *getPlayerById(std::string id);
    std::vector<Player *> getPlayerByPos(sf::Vector2i pos);
    std::vector<Player *> getPlayerByTeam(std::string name);
    std::vector<Player *> getPlayerByTeammateId(std::string id);
    bool teamExist(std::string tn);
private:
    void addPlayer(e_orientation o, sf::Vector2i pos, std::string team, std::string id);
    e_character getRightCharacter(std::string s);

    std::vector<Player*> _players;
    std::vector<std::pair<std::string, e_character>> _teamRegistered;
};

#endif