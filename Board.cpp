#include "Board.h"
#include "Game.h"
Board::Board(): width(WIDTH), height(HEIGHT)
{
    if(!gridImage.loadFromFile("images/board.png"))
        throw ExceptionSFML("Ошибка загрузки картинки игрового поля");
    gridTexture.loadFromImage(gridImage);
    gridSprite.setTexture(gridTexture);
    initializeVector();
}

sf::Sprite& Board::getGridSprite()
{
    return gridSprite;
}

int Board::getGameBoard (int x, int y) const
{
    return gameBoard[x][y];
}
void Board::setGameBoard(int x, int y, int value)
{
    gameBoard[x][y] = value;
}

int Board::getWidth() const
{
    return width;
}
int Board::getHeight() const
{
    return height;
}

void Board::initializeVector()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            gameBoard[i][j] = 0;
        }
    }
    for(int i = 0; i < width; ++i)
        gameBoard[height][i] = 1;

}

void Board::drawGameBoard(sf::RenderWindow &window)
{
    window.draw(gridSprite);
}

Board::~Board()
{

}





