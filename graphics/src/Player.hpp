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
        Player(e_orientation o, sf::Vector2i pos, std::string teamName, std::string id);
        ~Player();
        
        // Get stage of the player
        int getStage();
        
        // Set stage for this player
        void setStage(int stage);
        
        // Getter for head mEntity
        mEntity *getHead();
        
        // Getter for body mEntity
        mEntity *getBody();
        
        // Update player, call update for head and body and change the animation loop based on orientation
        void update();
        
        // Return orientation
        e_orientation getOrientation();
        
        // Set Orientation
        void setOrientation(e_orientation o);
        
        // Get position goal, the position the pllayer should be in
        sf::Vector2i getPositionGoal();
        
        // Set a new position goal, can't be anything else than a neighbor of currnet position
        void setPositionGoal(sf::Vector2i np);

        // Return actuel position
        sf::Vector2i getPosition();
        
        // Movement ofset functiun are only used for the movement of the player between cell
        void resetMovementOffset();
        void addMovementOffset(sf::Vector2f toAdd);
        sf::Vector2f getMovementOffset();

        // Called once the player reach the position cell
        void updatePosition();
        
        // return the time passed to walk, in milliseconds
        int64_t getTimeMillisecond();
        
        
        void setIdle();
        // Return x pos on grid
        int x();
        // Return y pos on grid
        int y();

        // return team name
        std::string getTeamName();

        // return get id
        std::string getId();

        // return life
        int getLife();
        // set Life
        void setLife(int i);
    private:
        int _stage;
        int _life;
        std::string _id;
        std::string _teamName;
        sf::Vector2i _position;
        sf::Vector2i _positionGoal;
        sf::Vector2f _movementOffset;
        mEntity *_head;
        mEntity *_body;
        e_orientation _orientation;
        sf::Clock _clock;

};

#endif