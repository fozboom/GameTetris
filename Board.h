#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

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
    sf::Sprite& getGridSprite();
    void drawGameBoard (sf::RenderWindow& window);
    int getGameBoard (int x, int y) const;
    void setGameBoard(int x, int y, int value);
    void initializeVector ();
    int getWidth() const;
    int getHeight() const;
    ~Board();
};


#endif //TETRIS_BOARD_H
