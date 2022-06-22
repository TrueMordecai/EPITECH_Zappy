#include "Network.hpp"

Network::Network()
{
    _font.loadFromFile("./assets/hud/font1.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(54);
    _text.setFillColor(sf::Color::Blue);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
    _text.setPosition(50, 900);
    
    //this->_preload.push_back("player new S 0 5 LesRats Hitrat");
    //this->_preload.push_back("player new S 1 5 LesRats Remy");
    //this->_preload.push_back("player new S 2 5 LesRats Gitan");
    //this->_preload.push_back("player new S 3 5 LesRats JeanDuratdin");
    _socket.setBlocking(false);
    _text.setString(_buffer);
}

Network::~Network()
{
    
}

static std::vector<std::string> split(std::string s, std::string del = " ")
{
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
    if (s.back() == '\n')
        s.pop_back();
    vec.push_back(s);
    return (vec);
}

std::vector<std::string> Network::manualCommand(sf::Event e)
{
    char a = static_cast<char>(e.text.unicode);
    std::string save;

    if (!_preload.empty() and e.type == sf::Event::TextEntered and _buffer == "" and e.text.unicode == 13) {
        save = _preload[_preload.size()-1];
        _preload.pop_back();
        return split(save);
    }
    if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == sf::Keyboard::Up) {
            _historyIndex++;
            if (_historyIndex < _history.size())
                _buffer = _history[_historyIndex];
            else  {
                _historyIndex = _history.size() - 1;
                _buffer = "";
            }
        }
        if (e.key.code == sf::Keyboard::Down) {
            _historyIndex--;
            if (_historyIndex < 0) {
                _historyIndex = 0;
                _buffer = "";
            }
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

static void DEBUG_print_vvs(std::vector<std::vector<std::string>> vs)
{
    int i = 0;
    int j = 0;
    for (std::vector<std::string> v : vs) {
        if (vs[0].size() < 1)
            return;
        std::cout << "Vector[" << i << "]\n";
        for (std::string s : v) {
            std::cout << "\tString[" << j << "] : " << s << "\n";
            j++;
        }
        i++;
        j = 0;
    }
}

std::vector<std::vector<std::string>> Network::serverCommand()
{
    std::vector<std::vector<std::string>> s;
    char data[1000];
    std::memset(data, 0, 1000);
    std::vector<std::string> bfr;
    size_t received;
    
    if (_socket.receive(data, 1000, received) != sf::Socket::NotReady) {
        bfr = split(data, "\n");
        for (auto v : bfr) 
            s.push_back(split(v));
    }
    if (_msz.x == 0) {
        for (auto vs : s) {
            if (vs.size() == 3) {
                if (vs[0] == "msz") {
                    _msz = {std::atoi(vs[1].c_str()), std::atoi(vs[2].c_str())};
                }
            }
        }
    }
    //DEBUG_print_vvs(s);
    return s;
}

sf::Text Network::getText()
{
    _text.setString(_buffer);
    return _text;
}

void Network::connect(std::string ip, int port)
{
    
    _socket.connect(ip, port);
    std::size_t sent = 13;
    _socket.send("GUI GUI GUI\n", 12, sent);
}

void Network::connect()
{
    _socket.connect(_ip, _port);
//    _socket.send("GUI GUI GUI\n", 12);
}

sf::Vector2i Network::getMapSize(void)
{
    return _msz;
}

void Network::setInfo(std::string ip, int port)
{
    _ip = ip;
    _port = port;
}