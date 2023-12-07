#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "header.h"

// Игровое поле для Тетриса
class Board
{

protected:
    sf::Image gridImage;  // Изображение для игрового поля
    sf::Texture gridTexture;  // Текстура, созданная из этого изображения
    sf::Sprite gridSprite;  // Спрайт, созданный из этой текстуры
    int width;  // Ширина игрового поля
    int height; // Высота игрового поля
    int gameBoard[HEIGHT + 1][WIDTH];  // Массив, представляющий игровое поле

public:
    // Конструктор и деструктор
    Board();
    ~Board();
    // Методы для управления спрайтом игрового поля
    sf::Sprite& getGridSprite();
    void drawGameBoard (sf::RenderWindow& window);
    // Методы для управления игровым полем
    int getGameBoard (int x, int y) const;
    void setGameBoard(int x, int y, int value);
    void initializeVector ();
    // Методы для получения размеров игрового поля
    int getWidth() const;
    int getHeight() const;
};



#endif //TETRIS_BOARD_H