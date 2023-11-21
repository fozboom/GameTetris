#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H
#include "header.h"

class Game
{
protected:
    Board field;

    Figure* currentFigure;
    Figure* nextFigure;

    Button buttonPause;
    Button buttonRestart;
    Button buttonMusic;
    Button buttonGameOver;
    Button buttonRowsCount;

    std::vector<Figure*> figures;
    my_Sprite oneBlock;
    my_Sprite pauseBoard;
    sf::Font font;
    sf::Text text;
    int lines_in_a_row;
    int score;
    int time;
    int fileTime;
    int tmpTime;
    int countLines;
    sf::Clock gameTime;
    std::string number;
    std::string nickName;

    sf::Music music;
    bool isLoadFromFile;

public:
    PlayerInfo infoBlock[COUNT_PEOPLE];
public:
    Game();
    int keyPressCheck(sf::Event& event, sf::RenderWindow& window, int& key, GameMenu& menu);
    int mousePressedCheck(sf::Event& event, sf::RenderWindow& window);
    void buttonAction (int& key);
    void fallingFigure (sf::Clock& timer, float pause);
    Figure*& getRandomFigure();
    void getAllFigures();
    void drawBoardImage (sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void drawNextFigureBlock(sf::RenderWindow& window);
    bool boundariesIsBroken ();
    void isLocked();
    int distanceToLocked ();
    void drawGrid(sf::RenderWindow& window);
    bool gameOver(sf::RenderWindow& window, sf::Event& event);
    void lineFilled ();
    void deleteLine (int num, int count);
    void readFileBestPlayers(const char* fileName);
    void writeFileBestPlayers(const char* fileName);
    void showBestPlayersBlock(sf::RenderWindow& window);
    void scoreBooster (int& _lines_in_a_row);
    void showGameTime(sf::RenderWindow& window);
    void showScore (sf::RenderWindow& window);
    void checkStatisticBeforeSave();
    bool drawWindow (sf::RenderWindow& window, GameMenu& menu);
    int getFieldGameBoard(int i, int j){return field.getGameBoard(i, j);}
    void setFieldGameBoard(int i, int j, int val){return field.setGameBoard(i, j, val);}
    int getScore()const {return score;}
    int getTime() const {return time;}
    void setScore (int _score){this->score = _score;}
    void setTime (int _time){ this->time = _time;}
    void loadGameFromFile(std::string fileName);
    void saveGameToFile(std::string fileName);
    void setIsLoadFromFile(bool val){isLoadFromFile = val;}
};


#endif //TETRIS_GAME_H