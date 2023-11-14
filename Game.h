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
    my_Sprite oneBlock;
    sf::Font font;
    sf::Text text;
    int lines_in_a_row;
    int score = 10000;
    int time;
    sf::Clock gameTime;
    std::string number;
public:
    PlayerInfo infoBlock[COUNT_PERSONS];
public:
    Game();
    void keyPressCheck(sf::Event& event, int& key, sf::RenderWindow& window);
    void buttonAction (int& key);
    void fallingFigure (sf::Clock& timer, float pause);
    Figure*& getRandomFigure();
    void getAllFigures();
    void draw(sf::RenderWindow& window);
    void drawNextFigureBlock(sf::RenderWindow& window);
    bool boundariesIsBroken ();
    void isLocked();
    int distanceToLocked ();
    void drawGrid(sf::RenderWindow& window);
    bool gameOver();
    void lineFilled ();
    void deleteLine (int num, int count);
    void readFileBestPlayers(const char* fileName);
    void writeFileBestPlayers(const char* fileName);
    void showBestPlayersBlock(sf::RenderWindow& window);
    void scoreBooster (int& _lines_in_a_row);
    void showGameTime(sf::RenderWindow& window);
    void showScore (sf::RenderWindow& window);
};


#endif //TETRIS_GAME_H