#include "Player.hpp"

Player::Player(e_orientation o, sf::Vector2i pos, std::string teamName, std::string id, e_character c)
{
    
    this->_head = new mEntity("assets/fullSheet.png", sf::IntRect(0, 0 , 0, 0), 99, 1, LEFT_TO_RIGHT, "TexLoad");
    
    //std::cout << e_character;
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

    _head->addAnimationLoop("stage7D", 2, 300, sf::IntRect(0, 8, 56, 30));
    _head->addAnimationLoop("stage7R", 2, 300, sf::IntRect(112, 208, 56, 30));
    _head->addAnimationLoop("stage7U", 2, 300, sf::IntRect(224, 208, 56, 30));
    _head->addAnimationLoop("stage7L", 2, 300, sf::IntRect(336, 208, 56, 30));

    _head->addAnimationLoop("stage8D", 2, 300, sf::IntRect(0,   240, 58, 30));
    _head->addAnimationLoop("stage8R", 2, 300, sf::IntRect(116, 240, 58, 30));
    _head->addAnimationLoop("stage8U", 2, 300, sf::IntRect(232, 240, 58, 30));
    _head->addAnimationLoop("stage8L", 2, 300, sf::IntRect(348, 240, 58, 30));


    this->_character = c;
    this->_accesories = new mEntity("assets/fullSheet.png", sf::IntRect(0, 0, 0, 0), 99, 1, LEFT_TO_RIGHT, "Texload");
    
    _accesories->addAnimationLoop("D", 2, 300, sf::IntRect(224, 369 + 32 * (_character - 1), 32, 26));
    _accesories->addAnimationLoop("R", 2, 300, sf::IntRect(224 + 64, 369 + 32 * (_character - 1), 32, 26));
    _accesories->addAnimationLoop("U", 2, 300, sf::IntRect(224 + 128, 369 + 32 * (_character - 1), 32, 26));
    _accesories->addAnimationLoop("L", 2, 300, sf::IntRect(224 + 192, 369 + 32* (_character - 1), 32, 26));

    this->_body = new mEntity("assets/fullSheet.png", sf::IntRect(0, 0, 0, 0), 99, 1, LEFT_TO_RIGHT, "TexLoad");


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
    _accesories->getSprite().setScale(sf::Vector2f(4, 4));

    _stage = 1;
    _movementOffset = {0, 0};
    _position = pos;
    _positionGoal = pos;
    _orientation = o;
    _teamName = teamName;
    _id = id;
    _life = 65;

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
    //_accesories->getClock().restart();
    //_head->getClock().restart();
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

mEntity* Player::getAccesories()
{
    return _accesories;
}

void Player::update()
{
    _accesories->update();
    _accesories->synchronize(*_head);
    std::string h = "stage";
    if (_stage <= 3)
        h += std::to_string(1);
    else
        h += std::to_string(_stage);
    
    if (_orientation == LEFT) {
        h += std::string("L");
        _accesories->changeAnimationLoop("L");
    }
    if (_orientation == RIGHT) {
        h += std::string("R");
        _accesories->changeAnimationLoop("R");
    }
    if (_orientation == UP) {
        h += std::string("U");
        _accesories->changeAnimationLoop("U");
    }
    if (_orientation == DOWN) {
        h += std::string("D");
        _accesories->changeAnimationLoop("D");
    }
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
    if (_position != _positionGoal)
        return;
    if (abs(np.x - _position.x + abs(np.y - _position.y)) > 1)
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
        if (_orientation == LEFT or _orientation == RIGHT) {
            _body->changeAnimationLoop("LRwhiteidle");
        } else {
            _body->changeAnimationLoop("UDwhiteidle");
        }
    } else {
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

std::string Player::getTeamName()
{
    return _teamName;
}

std::string Player::getId()
{
    return (_id);
}

int Player::getLife()
{
    return _life;
}

void Player::setLife(int i)
{
    _life = i;
}

e_character Player::getCharacter()
{
    return _character;
}
