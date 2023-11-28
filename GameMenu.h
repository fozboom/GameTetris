#ifndef TETRIS_GAMEMENU_H
#define TETRIS_GAMEMENU_H

#include "Picture.h"
#include "header.h"

class Button;
class Game;

class GameMenu
{
private:
    int selectedMenuOption;
    int key;
    Button *buttonStart;
    Button *buttonResume;
    Button *buttonExit;
    Picture mainMenu;
    bool isMenu;
public:
    GameMenu();
    void showMenu(sf::RenderWindow& window, Game& game);
    void keyPressCheck(sf::Event& event);
    void buttonAction(Game& game);
    bool getIsMenu() const;
    void setIsMenu(bool x);
    ~GameMenu();
};

#endif //TETRIS_GAMEMENU_H
