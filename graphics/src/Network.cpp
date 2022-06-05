#include "Network.hpp"

Network::Network()
{
    _font.loadFromFile("./assets/hud/font1.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(54);
    _text.setFillColor(sf::Color(54, 45, 45));
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
    _text.setPosition(50, 900);
    _buffer = "";
    _text.setString(_buffer);
}

Network::~Network()
{
    
}

static std::vector<std::string> split(std::string s)
{
    std::string del = " ";

    size_t pos = 0;
    std::string token;
    std::vector<std::string> vec;

    if (s == "")
        return vec;
    while ((pos = s.find(del)) != std::string::npos) {
        token = s.substr(0, pos);
        vec.push_back(token);
        s.erase(0, pos + del.length());
    }
    vec.push_back(s);
    return (vec);
}

std::vector<std::string> Network::manualCommand(sf::Event e)
{
    char a = static_cast<char>(e.text.unicode);
    std::string save;

    if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == sf::Keyboard::Up) {
            _historyIndex++;
            if (_historyIndex < _history.size())
                _buffer = _history[_historyIndex];
            else 
                _buffer = "";
        }
        if (e.key.code == sf::Keyboard::Down) {
            _historyIndex--;
            if (_historyIndex < 0)
                _historyIndex = 0;
            if (_history.size() > 1)
                _buffer = _history[_historyIndex];
            else 
                _buffer = "";
        }
        return(split(""));
    }
    if (e.text.unicode == 8) { // if delete
        if (_buffer.size() > 0) { // if buffer isn't empty
            _buffer.pop_back(); // Remove last element
        }
        return (split("")); // Return nothing
    }
    if (e.text.unicode == 13) { // If enter
        if (_buffer == "")
            return (split(""));
        save = _buffer;
        _history.push_back(save); // Save in command history;
        _historyIndex = -1;
        _buffer.clear(); // Clear buffer
        return (split(save)); // Return the buffer splited by " "
    }
    _buffer += a; // Add the character typed
    return (split(""));
}

sf::Text Network::getText()
{
    _text.setString(_buffer);
    return _text;
}