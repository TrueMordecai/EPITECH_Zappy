#include "Player.hpp"

Player::Player()
{
    
    this->_head = new mEntity("assets/fullSheet.png", sf::IntRect(0, 0 , 0, 0), 99, 1, LEFT_TO_RIGHT, "TexLoad");
    
    _head->addAnimationLoop("stage1D", 2, 300, sf::IntRect(0, 0, 32, 26));
    _head->addAnimationLoop("stage1R", 2, 300, sf::IntRect(64, 0, 32, 26));
    _head->addAnimationLoop("stage1U", 2, 300, sf::IntRect(128, 0, 32, 26));
    _head->addAnimationLoop("stage1L", 2, 300, sf::IntRect(192, 0, 32, 26));


    _head->addAnimationLoop("stage4D", 2, 300, sf::IntRect(0, 96, 32, 26));
    _head->addAnimationLoop("stage4R", 2, 300, sf::IntRect(64, 96, 32, 26));
    _head->addAnimationLoop("stage4U", 2, 300, sf::IntRect(128, 96, 32, 26));
    _head->addAnimationLoop("stage4L", 2, 300, sf::IntRect(192, 96, 32, 26));

    _head->addAnimationLoop("stage5D", 2, 300, sf::IntRect(0,   128, 32, 26));
    _head->addAnimationLoop("stage5R", 2, 300, sf::IntRect(64,  128, 32, 26));
    _head->addAnimationLoop("stage5U", 2, 300, sf::IntRect(128, 128, 32, 26));
    _head->addAnimationLoop("stage5L", 2, 300, sf::IntRect(192, 128, 32, 26));

    _head->addAnimationLoop("stage6D", 2, 300, sf::IntRect(0,   160, 50, 33));
    _head->addAnimationLoop("stage6R", 2, 300, sf::IntRect(100, 160, 50, 33));
    _head->addAnimationLoop("stage6U", 2, 300, sf::IntRect(200, 160, 50, 33));
    _head->addAnimationLoop("stage6L", 2, 300, sf::IntRect(300, 160, 50, 33));

    _head->addAnimationLoop("stage7D", 2, 300, sf::IntRect(0,   208, 56, 30));
    _head->addAnimationLoop("stage7R", 2, 300, sf::IntRect(112, 208, 56, 30));
    _head->addAnimationLoop("stage7U", 2, 300, sf::IntRect(224, 208, 56, 30));
    _head->addAnimationLoop("stage7L", 2, 300, sf::IntRect(336, 208, 56, 30));

    _head->addAnimationLoop("stage8D", 2, 300, sf::IntRect(0,   240, 58, 30));
    _head->addAnimationLoop("stage8R", 2, 300, sf::IntRect(116, 240, 58, 30));
    _head->addAnimationLoop("stage8U", 2, 300, sf::IntRect(232, 240, 58, 30));
    _head->addAnimationLoop("stage8L", 2, 300, sf::IntRect(348, 240, 58, 30));


    this->_body = new mEntity("assets/fullSheet.png", sf::IntRect(0, 0, 0, 0), 99, 1, LEFT_TO_RIGHT,"TexLoad");

    _body->addAnimationLoop("UDwhiteidle", 1, 95, sf::IntRect(0, 272, 32, 16));
    _body->addAnimationLoop("UDwhite",10 , 95, sf::IntRect(0, 272, 32, 16));
    _body->addAnimationLoop("LRwhiteidle", 1, 95, sf::IntRect(0, 288, 32, 16));
    _body->addAnimationLoop("LRwhite",10 , 95, sf::IntRect(0, 288, 32, 16));    

    _body->addAnimationLoop("UDblackidle",1 , 95, sf::IntRect(0, 304, 32, 16));
    _body->addAnimationLoop("UDblack",10 , 95, sf::IntRect(0, 304, 32, 16));
    _body->addAnimationLoop("LRblackidle",10 , 95, sf::IntRect(0, 320, 32, 16));
    _body->addAnimationLoop("LRblack",10 , 95, sf::IntRect(0, 320, 32, 16));

    _head->getSprite().setScale(sf::Vector2f(4, 4));
    _body->getSprite().setScale(sf::Vector2f(4, 4));
    _stage = 7;

    _movementOffset = {0, 0};
    _position = sf::Vector2i(4, 5);
    _positionGoal = sf::Vector2i(5, 5);
    _orientation = e_orientation::DOWN;

    
    ///// SHOULDN'T BE USEFUL
    getBody()->getSprite().setPosition(sf::Vector2f(x() * 128, y() * 128 + 32));
    /////////////////////////
}

Player::~Player()
{
    
}

int Player::getStage()
{
    return _stage;
}

void Player::setStage(int stage)
{
    _stage = stage;
}

mEntity* Player::getHead()
{
    return _head;
}

mEntity* Player::getBody()
{
    return _body;
}

void Player::update()
{
    std::string h = "stage";
    if (_stage <= 3)
        h += std::to_string(1);
    else
        h += std::to_string(_stage);
    if (_orientation == LEFT)
        h += std::string("L");
    if (_orientation == RIGHT)
        h += std::string("R");
    if (_orientation == UP)
        h += std::string("U");
    if (_orientation == DOWN)
        h += std::string("D");
    _head->changeAnimationLoop(h);
    _head->update();


    std::string b = "";
    if (_orientation == DOWN or _orientation == UP)
        b += "UD";
    else
        b += "LR";
    if (_stage < 4)
        b += "white";
    else
        b += "black";
    _body->changeAnimationLoop(b);
    if (_positionGoal == _position)
        setIdle();
    _body->update();
}

e_orientation Player::getOrientation()
{
    return _orientation;
}

void Player::setOrientation(e_orientation o)
{
    _orientation = o;
}

sf::Vector2i Player::getPositionGoal()
{
    return _positionGoal;
}

sf::Vector2i Player::getPosition()
{
    return _position;
}

void Player::resetMovementOffset()
{
    _movementOffset = {0, 0};
}

void Player::addMovementOffset(sf::Vector2f toAdd)
{
    _movementOffset.x += toAdd.x;
    _movementOffset.y += toAdd.y;
}

sf::Vector2f Player::getMovementOffset()
{
    return _movementOffset;
}

void Player::setPositionGoal(sf::Vector2i np)
{
    if (abs(np.x - _position.x) > 1)
        return;
    if (abs(np.y - _position.y) > 1)
        return;
    _clock.restart();
    _positionGoal = np;
}

void Player::updatePosition()
{
    _position = _positionGoal;
    this->setIdle();
}

void Player::setIdle()
{
    if (_stage <= 3) {
        std::cout << "Should idle\n";
        if (_orientation == LEFT or _orientation == RIGHT) {
            _body->changeAnimationLoop("LRwhiteidle");
        } else {
            _body->changeAnimationLoop("UDwhiteidle");
        }
    } else {
        std::cout << "Should idle\n";
        if (_orientation == LEFT or _orientation == RIGHT) {
            _body->changeAnimationLoop("LRblackidle");
        } else {
            _body->changeAnimationLoop("UDblackidle");
        }
    }
}

int64_t Player::getTimeMillisecond()
{
    return _clock.getElapsedTime().asMilliseconds();
}

int Player::x()
{
    return _position.x;
}

int Player::y()
{
    return _position.y;    
}
