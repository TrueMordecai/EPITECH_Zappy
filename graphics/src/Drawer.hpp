#include "Player.hpp"
class Drawer
{
public:
    Drawer(/* args */);
    ~Drawer();
    void drawPlayer(Player &p);
    void display();
    void clear();
    bool loop();
private:
    void drawStage2(Player &p, mEntity *curHead);
    void drawStage3(Player &p, mEntity *curHead);
    void drawStage4(Player &p, mEntity *curHead);
    void drawStage5(Player &p, mEntity *curHead);
    void drawStage6(Player &p, mEntity *curHead);
    void drawStage7(Player &p, mEntity *curHead);
    void drawStage8(Player &p, mEntity *curHead);
    void drawHead(Player &p, mEntity *curHead);
    void drawBody(Player &p, mEntity *curBody);
    
    mEntity *_normal;
    mEntity *_black;
    sf::RenderWindow *_window;
    mEntity *_stage2;
    mEntity *_stage3;
    mEntity *_stage4;
    mEntity *_stage5;
    mEntity *_stage6;
    mEntity *_stage7;
    mEntity *_stage8;
};
