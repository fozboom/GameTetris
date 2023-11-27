#ifndef TETRIS_GAMEMENU_H
#define TETRIS_GAMEMENU_H
#include "header.h"


class Game;

class GameMenu
{
private:
    int selectedMenuOption;
    int key;
    Picture buttonStart;
    Picture buttonResume;
    Picture buttonExit;
    bool isMenu;
public:
    GameMenu();
    void showMenu(sf::RenderWindow& window, Game& game);
    void keyPressCheck(sf::Event& event);
    void buttonAction(Game& game);
    bool getIsMenu() const;
    void setIsMenu(bool x);
};

#endif //TETRIS_GAMEMENU_H
