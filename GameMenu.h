#ifndef TETRIS_GAMEMENU_H
#define TETRIS_GAMEMENU_H
#include "header.h"


class Game;

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
    void showMenu(sf::RenderWindow& window, Game& game);
    void keyPressCheck(sf::Event& event);
    void buttonAction(Game& game);
    bool getIsMenu() const {return isMenu;}
    void setIsMenu(bool x){isMenu = x;}
    void saveGameToFile(std::string fileName, Game& game);
    void loadGameFromFile (std::string fileName,Game& game);
};




#endif //TETRIS_GAMEMENU_H
