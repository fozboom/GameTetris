#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H
#include "header.h"

class Game
{
protected:
    Board field;
    Figure* currentFigure;
    Figure* nextFigure;
    std::vector<Figure*> figures;
    //my_Sprite background;
    my_Sprite oneBlock;
    //my_Sprite blockNextFigure;
public:
    Game();
    void keyPressCheck(sf::Event& event, int& key, sf::RenderWindow& window);
    void buttonAction (int& key, Game& game);
    void fallingFigure (sf::Clock& timer, float pause, Game& game);
    Figure* getRandomFigure();
    std::vector<Figure*> getAllFigures();
    void draw(sf::RenderWindow& window);
    bool boundariesIsBroken ();
    void isLocked();
    int distanceToLocked ();
    void drawGrid(sf::RenderWindow& window);
    bool gameOver();
    void lineFilled ();
    void deleteLine (int k);

};


#endif //TETRIS_GAME_H
