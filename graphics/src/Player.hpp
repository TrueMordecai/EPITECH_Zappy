#include "mEntity.hpp"

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

enum e_orientation {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

class Player
{
    public:
        Player();
        ~Player();
        int getStage();
        void setStage(int stage);
        mEntity *getHead();
        mEntity *getBody();
        void update();
        e_orientation getOrientation();
        void setOrientation(e_orientation o);
        sf::Vector2i getPositionGoal();
        sf::Vector2i getPosition();
        void resetMovementOffset();
        void addMovementOffset(sf::Vector2f toAdd);
        sf::Vector2f getMovementOffset();
        void setPositionGoal(sf::Vector2i np);
        void updatePosition();
        int64_t getTimeMillisecond();
        void setIdle();
        int x();
        int y();
    private:
        int _stage;
        sf::Vector2i _position;
        sf::Vector2i _positionGoal;
        sf::Vector2f _movementOffset;
        mEntity *_head;
        mEntity *_body;
        e_orientation _orientation;
        sf::Clock _clock;

};

#endif