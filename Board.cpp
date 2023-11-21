#include "Board.h"
#include "Game.h"
Board::Board(): width(WIDTH), height(HEIGHT)
{
    gridImage.loadFromFile("images/board.png");
    gridTexture.loadFromImage(gridImage);
    gridSprite.setTexture(gridTexture);
    initializeVector();
}


void Board::initializeVector()
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            gameBoard[i][j] = 0;
        }
    }
    for(int i = 0; i < WIDTH; ++i)
        gameBoard[HEIGHT][i] = 1;

}

void Board::drawGameBoard(sf::RenderWindow &window)
{
    //gridSprite.setPosition(30*18, 30*5);
    window.draw(gridSprite);
}





