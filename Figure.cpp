#include "Figure.h"

// Конструктор класса Block
Block::Block(int x, int y)
{
    this->x = x; // Установка значения координаты x для блока
    this->y = y; // Установка значения координаты y для блока
}

// Функция для генерации случайного числа в заданном диапазоне
int generateRandomNumber(int a, int b)
{
    std::random_device rd; // Инициализация генератора случайных чисел
    std::mt19937 gen(rd()); // Использование Mersenne Twister алгоритма
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(gen); // Генерация случайного числа
}

// Конструктор класса Figure
Figure::Figure(): shadowCube("./images/shadow_cube.png",0,0), cubeImage("./images/color_cubes.png", 0,0), type(0), cellSize(30), offsetX(4), offsetY(0), distanceToCollision(0)
{
    rotationStatus = 0; // Установка начального статуса вращения фигуры
    color = generateRandomNumber(1, 3); // Генерация случайного цвета фигуры
}

// Методы получения приватных полей класса
int Figure::getType() const
{
    return type;
}
int Figure::getColor() const
{
    return color;
}

// Установка дистанции до столкновения
void Figure::setDistanceToCollision(int x)
{
    distanceToCollision = x;
}

// Получение текущего статуса фигуры
std::vector<Block>& Figure::getStatus()
{
    return status;
}

// Получение смещения фигуры по осям x и y
int Figure::get_offset_x() const
{
    return offsetX;
}
int Figure::get_offset_y() const
{
    return offsetY;
}

// Функция отрисовки фигуры
void Figure::drawFigure(sf::RenderWindow& window)
{
    std::vector<Block> tmp = calculateMovedPosition( );

    cubeImage.sprite.setTextureRect(sf::IntRect((color-1) * cellSize,0,cellSize , cellSize) );
    shadowCube.sprite.setTextureRect(sf::IntRect((color-1) * cellSize,0,cellSize , cellSize) );
    for (Block& item: tmp)
    {
        cubeImage.sprite.setPosition(static_cast<float>(item.x*cellSize +576), static_cast<float>(item.y*cellSize + 175));
        window.draw(cubeImage.sprite);
        if (distanceToCollision >= heightOfBlock)
        {
            shadowCube.sprite.setPosition(static_cast<float>(item.x * cellSize + 576),
                                          static_cast<float>(item.y * cellSize + 175 + distanceToCollision * CELL_SIZE));
            window.draw(shadowCube.sprite);
        }
    }

}

// Функция перемещения фигуры
void Figure::move(int x, int y)
{
    this->offsetX += x;
    this->offsetY += y;
}

// Расчет переместившегося положения фигуры
std::vector<Block> Figure::calculateMovedPosition()
{
    std::vector<Block> tmp = status;
    std::vector<Block> movedCondition;
    for (auto & i : tmp)
    {
        Block pos = Block(i.x + offsetX, i.y + offsetY);
        movedCondition.push_back(pos);
    }
    return movedCondition;
}

// Деструктор класса Figure
Figure::~Figure()
{
    status.clear();
}

// Деструктор класса Block

Block::~Block()
{

}