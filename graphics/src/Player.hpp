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
        void setStage();
        mEntity *getHead();
        mEntity *getBody();
        void update();
        e_orientation getOrientation();
        void setOrientation(e_orientation o);
    private:
        int _stage;
        mEntity *_head;
        mEntity *_body;
        e_orientation _orientation;
};

#endif