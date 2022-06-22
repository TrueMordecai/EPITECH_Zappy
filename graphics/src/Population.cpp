#include "Population.hpp"

Population::Population()
{
    
}

Population::~Population()
{
    
}

static e_orientation getOrientation(std::string s)
{
    if (s == "N" or s == "0")
        return (e_orientation::UP);
    if (s == "S" or s == "2")
        return (e_orientation::DOWN);
    if (s == "E" or s == "1")
        return (e_orientation::RIGHT);
    if (s == "W" or s == "3")
        return (e_orientation::LEFT);
    std::cout << "ERROR : Wrong orientation string\n";
    return (e_orientation::LEFT);
}

static e_orientation rotate(std::string s, e_orientation o)
{
    if (s == "L") {
        switch (o) {
        case UP:
            return LEFT;
        case LEFT:
            return DOWN;
        case DOWN:
            return RIGHT;
        case RIGHT:
            return UP;
        }
    }
    if (s == "R") {
        switch (o) {
        case UP:
            return RIGHT;
        case LEFT:
            return UP;
        case DOWN:
            return LEFT;
        case RIGHT:
            return DOWN;
        }
    }
    std::cout << "ERROR : Wrong orientation letter, should be either L or R\n";
    return (UP);
}

sf::Vector2i forward(sf::Vector2i p, e_orientation o)
{
    if (o == LEFT)
        return {p.x - 1, p.y};
    if (o == RIGHT)
        return {p.x + 1, p.y};
    if (o == UP)
        return {p.x, p.y -1};
    if (o == DOWN)
        return {p.x, p.y + 1};
    return {p.x, p.y + 1};
}

void Population::parseCommand(std::vector<std::string> c)
{
    if (c.size() < 1)
        return;
    if (c[0] != "player")
        return;
    if (c[1] == "new") {
        std::cout << "New Player ! Position = " << std::atoi(c[3].c_str()) << "/" << std::atoi(c[4].c_str()) << "\n";
        addPlayer(getOrientation(c[2]), {std::atoi(c[3].c_str()), std::atoi(c[4].c_str())}, c[5], c[6]);
    }
    if (c[1] == "rotate")
        getPlayerById(c[2])->setOrientation(rotate(c[3],  getPlayerById(c[2])->getOrientation()));
    if (c[1] == "move")
        getPlayerById(c[2])->setPositionGoal(forward(getPlayerById(c[2])->getPosition(), getPlayerById(c[2])->getOrientation()));
    if (c[1] == "life")
        getPlayerById(c[2])->setLife(std::atoi(c[3].c_str()));
    if (c[1] == "up")
        getPlayerById(c[2])->setStage(getPlayerById(c[2])->getStage() + 1);
}

Player *Population::getPlayerById(std::string id)
{
    for (unsigned int i = 0; i != getPlayers().size(); i++) {
        if (_players[i]->getId() == id)
            return (_players[i]);
    }
    return (nullptr);
}

bool Population::teamExist(std::string tn)
{
    for (unsigned int i = 0; i != _teamRegistered.size(); i++) {
        if (_teamRegistered[i].first == tn) {
            return true;
        }
    }
    return false;
}

std::vector<Player *> Population::getPlayerByPos(sf::Vector2i pos)
{
    std::vector<Player *> bfr;
    
    for (unsigned int i = 0; i != getPlayers().size(); i++) {
        if (_players[i]->getPosition() == pos)
            bfr.push_back(_players[i]);
    }
    if (bfr.size() == 0)
        bfr.push_back(nullptr);
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

std::vector<Player *> Population::getPlayerByTeammateId(std::string id)
{
    std::vector<Player *> bfr;
    
    Player *p = getPlayerById(id);
    if (!p)
        return (bfr);
    for (unsigned int i = 0; i != getPlayers().size(); i++) {
        if (_players[i]->getTeamName() == p->getTeamName() && _players[i]->getId() != id)
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
    if (getPlayerById(id) != nullptr) {
        std::cout << "Error : Player " << id << " already exist\n";
        return;
    }
    Player *p = new Player(o, pos, team, id, getRightCharacter(team));
    
    if (!teamExist(team)) {
        _teamRegistered.push_back(std::pair<std::string, e_character>(team, p->getCharacter()));
    }
    _players.push_back(p);
}

e_character Population::getRightCharacter(std::string s)
{
    e_character ret = C_ISAAC; 

    for (unsigned int i = 0; i != _teamRegistered.size(); i++) {
        if (s == _teamRegistered[i].first)
            return (_teamRegistered[i].second);
        if (_teamRegistered[i].second == ret) {
            ret = static_cast<e_character>(static_cast<int>(ret + 1));
        }
    }
    return ret;
}