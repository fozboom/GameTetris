#include "Board.h"
#include "Game.h"

// Конструктор по умолчанию.
// Задает ширину и высоту доски значениями по умолчанию (WIDTH, HEIGHT).
// Пытается загрузить изображение для игрового поля. Если неудачно, генерирует исключение.
// Загружает текстуру из изображения и задает её для спрайта.
// Инициализирует вектор игрового поля.
Board::Board(): width(WIDTH), height(HEIGHT)
{
    if(!gridImage.loadFromFile("images/board.png"))
        throw ExceptionSFML("Ошибка загрузки картинки игрового поля");
    gridTexture.loadFromImage(gridImage);
    gridSprite.setTexture(gridTexture);
    initializeVector();
}

// Возвращает спрайт игрового поля (как ссылку).
sf::Sprite& Board::getGridSprite()
{
    return gridSprite;
}

// Возвращает значение соответствующей клетки игрового поля.
int Board::getGameBoard(int x, int y) const
{
    return gameBoard[x][y];
}

// Устанавливает значение для соответствующей клетки игрового поля.
void Board::setGameBoard(int x, int y, int value)
{
    gameBoard[x][y] = value;
}

// Возвращает ширину игрового поля.
int Board::getWidth() const
{
    return width;
}

// Возвращает высоту игрового поля.
int Board::getHeight() const
{
    return height;
}

// Инициализирует вектор игрового поля заданными значениями.
// Все клетки в пределах заданной высоты и ширины устанавливаются в 0.
// Клетки в нижнем ряду устанавливаются в 1 (обозначение границы поля).
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

// Рисует игровое поле в окне.
void Board::drawGameBoard(sf::RenderWindow &window)
{
    window.draw(gridSprite);
}

// Деструктор класса "Доска" (или "Игровое Поле").
Board::~Board()
{

}