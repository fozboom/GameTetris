#ifndef TETRIS_GAMEMENU_H
#define TETRIS_GAMEMENU_H
#include "header.h"

class GameMenu
{
private:
    int typeOfMenu;
    int key;
    my_Sprite buttonStart;
    my_Sprite buttonResume;
    my_Sprite buttonExit;
    bool isMenu;
public:
    GameMenu();
    void showMenu(sf::RenderWindow& window);
    void keyPressCheck(sf::Event& event);
    void buttonAction();
    bool getIsMenu() const {return isMenu;}
    void setIsMenu(bool x){isMenu = x;}
};




#endif //TETRIS_GAMEMENU_H
