#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H
#include "header.h"
#include "Board.h"
#include "Figure.h"
#include "Button.h"
#include "Picture.h"
#include "Queue.h"
#include "GameMenu.h"
class Game
{
protected:
    Board field;

    Figure* currentFigure;
    Figure* nextFigure;
    std::vector<Figure*> figures;

    Button buttonPause;
    Button buttonRestart;
    Button buttonMusic;

    Picture buttonGameOver;
    Picture buttonRowsCount;
    Picture oneBlock;
    Picture pauseBoard;

    sf::Font font;
    sf::Text text;
    sf::Clock gameTime;
    sf::Music music;

    int lines_in_a_row;
    int score;
    int time;
    int fileTime;
    int tmpTime;
    int countLines;
    std::string number;
    std::string nickName;

    Queue<PlayerInfo> infoQueue;
public:

public:
    Game();
    int keyPressCheck(sf::Event& event, sf::RenderWindow& window, int& key, GameMenu& menu);
    int mousePressedCheck(sf::Event& event, sf::RenderWindow& window);
    void buttonAction (int& key);
    void fallingFigure (sf::Clock& timer, float pause);
    Figure* getRandomFigure();
    void getAllFigures();
    void drawBoardImage (sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void drawNextFigureBlock(sf::RenderWindow& window);
    bool boundariesIsBroken ();
    void isLocked();
    int distanceToLocked ();
    void drawPlacedBlocks(sf::RenderWindow& window);
    bool gameOver(sf::RenderWindow& window, sf::Event& event);
    void checkAndClearFilledLines ();
    void deleteLine (int num, int count);
    void readFileBestPlayers(const char* fileName);
    void writeFileBestPlayers(const char* fileName);
    void showBestPlayersBlock(sf::RenderWindow& window);
    void scoreBooster (int& _lines_in_a_row);
    void showGameTime(sf::RenderWindow& window);
    void showScore (sf::RenderWindow& window);
    void checkStatisticBeforeSave();
    bool processGameCycle (sf::RenderWindow& window, GameMenu& menu);
    void loadGameFromFile(std::string fileName);
    void saveGameToFile(std::string fileName);
    ~Game();
};


#endif //TETRIS_GAME_H