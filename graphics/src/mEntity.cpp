#include "mEntity.hpp"
#include <iostream> /// REOMVE !!

mEntityAnimation::mEntityAnimation(std::string name, int nbFrame, int64_t milli, sf::IntRect rect)
{
    _milliseconds = milli;
    _nbFrame = nbFrame;
    _name = name;
    _rect = rect;
}

mEntityAnimation::~mEntityAnimation()
{}

std::string mEntityAnimation::name()
{
    return (_name);
}

sf::IntRect mEntityAnimation::rect()
{
    return (_rect);
}

int mEntityAnimation::nbFrame()
{
    return (_nbFrame);
}

int64_t mEntityAnimation::milliseconds()
{
    return (_milliseconds);
}

mEntity::mEntity(sf::String path, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir/* = LEFT_TO_RIGHT*/, std::string namee /* = "DEFAULT"*/)
{
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(rect);
    _rect = rect;
    _clock.restart();
    _timingMilliseconds = milliseconds;
    _nbFrame = nbFrame;
    _dir = dir;
    _name = namee;
    if (namee != "DEFAULT" and namee != "") {
        mEntityAnimation toSave(namee, nbFrame, milliseconds, rect);
        _saved.push_back(toSave);
    }
}

mEntity::mEntity(sf::Texture texture, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir, std::string name)
{
    _texture = texture;
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(rect);
    _rect = rect;
    _clock.restart();
    _timingMilliseconds = milliseconds;
    _nbFrame = nbFrame;
    _dir = dir;
    _name = name;
    if (name != "DEFAULT" and name != "") {
        mEntityAnimation toSave(name, nbFrame, milliseconds, rect);
        _saved.push_back(toSave);
    }    
}


/// Problem : last frame is slightly longer.
int mEntity::update()
{
    sf::Time curTime = _clock.getElapsedTime();
    
    if (curTime.asMilliseconds() / _timingMilliseconds > _nbFrame - 1) {
        if (_queue.size() > 1) {
            this->changeAnimationLoop(_queue[0]);
            _queue.erase(_queue.begin());
            return (update());
        }
            
        _clock.restart();
        return (_nbFrame);
    }
    if (_dir == LEFT_TO_RIGHT)
        _sprite.setTextureRect(sf::IntRect(_rect.width * (curTime.asMilliseconds() / _timingMilliseconds) + _rect.left, _rect.top, _rect.width, _rect.height));    
    else if (_dir == TOP_TO_BOTTOM)
        _sprite.setTextureRect(sf::IntRect(_rect.left, _rect.width * (curTime.asMilliseconds() / _timingMilliseconds) + _rect.top, _rect.width, _rect.height));    

    return (curTime.asMilliseconds() / _timingMilliseconds);
}

void mEntity::addAnimationLoop(std::string name, int nbFrame, int64_t milli, sf::IntRect rect)
{
    _saved.push_back(mEntityAnimation(name, nbFrame, milli, rect));
}

mEntity::~mEntity()
{}

void mEntity::changeAnimationLoop(sf::IntRect rect, int64_t milliseconds, int nbFrame, std::string name/* = "DEFAULT"*/)
{
    _rect = rect;
    _timingMilliseconds = milliseconds;
    _nbFrame = nbFrame;
    _name = name;
    if (name != "DEFAULT" and name != "")
        _saved.push_back(mEntityAnimation(name, nbFrame, milliseconds, rect));
    _clock.restart();
}

void mEntity::changeAnimationLoop(std::string name)
{
    if (name == _name)
        return;
    for (auto &i : _saved) {
        if (i.name() == name && _name != name) {
            _rect = i.rect();
            _timingMilliseconds = i.milliseconds();
            _nbFrame = i.nbFrame();
            _name = i.name();
            _clock.restart();
            _sprite.setTextureRect(_rect);
        }
    }
}

void mEntity::display(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

bool mEntity::intersect(sf::Vector2f p)
{
    sf::IntRect r = this->getHitbox();
    if (p.x >= r.left && p.x <= r.left + r.width) {
        if (p.y >= r.top && p.y <= r.top + r.height) {
            return (true);
        }
    }
    return (false);
}

bool mEntity::intersect(sf::Vector2i p)
{
    sf::IntRect r = this->getHitbox();

    if (p.x >= r.left && p.x <= r.left + r.width) {
        if (p.y >= r.top && p.y <= r.top + r.height) {
            return (true);
        }
    }
    return (false);
}

bool mEntity::intersect(sf::Vector2u p)
{
    sf::IntRect r = this->getHitbox();
    if (p.x >= r.left && p.x <= r.left + r.width) {
        if (p.y >= r.top && p.y <= r.top + r.height) {
            return (true);
        }
    }
    return (false);
}

void mEntity::addToQueue(std::string s)
{
    _queue.push_back(s);
}

sf::IntRect mEntity::getHitbox()
{
    sf::IntRect result;
    sf::Vector2f sc = _sprite.getScale();
    sf::IntRect rect = this->_rect;
    sf::Vector2f pos = _sprite.getPosition();
    sf::Vector2f origin = _sprite.getOrigin();
    
    result.left = pos.x - (origin.x * sc.x);
    result.top = pos.y - (origin.y * sc.y);
    result.height = rect.height * sc.y;
    result.width = rect.width * sc.x;
    return (result);
}

sf::Sprite& mEntity::getSprite()
{
    return _sprite;
}

std::string mEntity::getName()
{
    return (_name);
}

int mEntity::getNbFrame()
{
    return (_nbFrame);
}
