/*
** EPITECH PROJECT, 2022
** EPITECH_JAM_3
** File description:
** mEntity
*/
#ifndef MENTITY_HPP_
#define MENTITY_HPP_
#include "SFML/Graphics.hpp"
#include <memory>
#include <iostream>

enum direction_e {
    LEFT_TO_RIGHT = 0,
    TOP_TO_BOTTOM,
};

class mEntityAnimation
{
    public:
        mEntityAnimation(std::string _name, int nbFrame, int64_t milli, sf::IntRect rect);
        ~mEntityAnimation();
        std::string name();
        int nbFrame();
        int64_t milliseconds();
        sf::IntRect rect();

    private:
        std::string _name;
        int _nbFrame;
        int64_t _milliseconds;
        sf::IntRect _rect;
};


class mEntity
{
public:
    mEntity(sf::String path, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir = LEFT_TO_RIGHT, std::string NAME = "");
    mEntity(sf::Texture texture, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir = LEFT_TO_RIGHT, std::string NAME = "");
    ~mEntity();

    void changeAnimationLoop(sf::IntRect rect, int64_t milliseconds, int nbFrame, std::string name = "DEFAULT");
    void changeAnimationLoop(std::string name);
    
    /// Return the current frame
    int update();

    /// Add a loop to _saved
    void addAnimationLoop(std::string name, int nbFrame, int64_t milli, sf::IntRect rect);

    void display(sf::RenderWindow &window);
    
    bool intersect(sf::Vector2f point);
    bool intersect(sf::Vector2i point);
    bool intersect(sf::Vector2u point);

    // Add preregister animation in the wait list
    void addToQueue(std::string animation);
    
    
    sf::IntRect getHitbox();
    sf::Sprite &getSprite();
    std::string getName();
    int getNbFrame();
private:
    std::vector<std::string> _queue;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Clock _clock;
    direction_e _dir;


    int64_t _timingMilliseconds;
    sf::IntRect _rect;
    int _nbFrame;
    std::string _name;
    std::vector<mEntityAnimation> _saved;
};
#endif /* !PARALLAX_HPP_ */
