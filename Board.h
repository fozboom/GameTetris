
#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H
#pragma once
#include "header.h"

class Board
{
protected:
    sf::Image gridImage;
    sf::Texture gridTexture;
    sf::Sprite gridSprite;
    int width;
    int height;
    int gameBoard[HEIGHT + 1][WIDTH];
public:
    Board();
    sf::Sprite& getGridSprite() {return gridSprite;}
    void drawGameBoard (sf::RenderWindow& window);
    int getGameBoard (int x, int y) {return gameBoard[x][y];}
    void setGameBoard(int x, int y, int value){gameBoard[x][y] = value;}
    void initializeVector ();


};


#endif //TETRIS_BOARD_H
