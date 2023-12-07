#ifndef TETRIS_FIGURE_H
#define TETRIS_FIGURE_H

#include "Picture.h"
#include "header.h"

// Функция для генерации случайного числа в определенном диапазоне
int generateRandomNumber(int a, int b);

// Класс Block, представляет собой отдельный блок тетриса
class Block
{
public:
    int x; // x-координата блока
    int y; // y-координата блока

    Block(int x, int y);// Конструктор с параметрами координат
    ~Block(); // Деструктор класса
};

// Базовый класс Figure, представляет одну фигурку в тетрисе
class Figure
{
protected:
    // Вектор блоков, из которых состоит фигурка
    // Общая картина зависит от положения и формы этих блоков
    std::vector <Block> status;
    // Номер текущего положения фигурки (поворот)
    int rotationStatus;
    // Цвет фигурки
    int color;
    // Установленные размеры ячейки, смещения по оси x и y,
    // высота блока и расстояние до столкновения
    int cellSize;
    int offsetX;
    int offsetY;
    int heightOfBlock;
    int distanceToCollision;
    // Образы фигурки и тени
    Picture cubeImage;
    Picture shadowCube;
    // Определяет тип фигуры (для специфических поведений)
    int type;
public:
    Figure();
    int getType() const;
    int getColor() const;
    void setDistanceToCollision(int x);
    void drawFigure(sf::RenderWindow& window);
    void move(int xPos, int yPos);
    std::vector<Block> calculateMovedPosition ();
    std::vector<Block>& getStatus();
    int get_offset_x() const;
    int get_offset_y() const;
    virtual void rotateFigure (bool flag) = 0;
    virtual ~Figure();
};

// Остальной код является определениями различных конкретных фигур,
// включая J_Block, Z_Block, T_Block, S_Block, L_Block, I_Block и O_Block.
// Каждый из этих классов предоставляет свои варианты поворота и формы.

class J_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    J_Block()
    {
        type = 1;
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(2, 1)};
        allRotationOptions[1] = {Block(1, 0), Block(1, 1), Block(1, 2), Block(0, 2)};
        allRotationOptions[2] = {Block(0, 0), Block(0, 1), Block(1, 1), Block(2, 1)};
        allRotationOptions[3] = {Block(0, 0), Block(1, 0), Block(0, 1), Block(0, 2)};
        status = allRotationOptions[0];
        heightOfBlock = 3;
    }
    void rotateFigure(bool flag) override
    {
        if (flag)
        {
            rotationStatus++;
            if (rotationStatus > 3)
                rotationStatus = 0;

            if (rotationStatus == 0 || rotationStatus == 3)
                heightOfBlock = 3;
            else
                heightOfBlock = 2;
        }
        else
        {
            rotationStatus--;
            if(rotationStatus < 0)
                rotationStatus = 3;

            if (rotationStatus == 0 || rotationStatus == 3)
                heightOfBlock = 3;
            else
                heightOfBlock = 2;
        }
        status = allRotationOptions[rotationStatus];
    }
    ~J_Block() override {};
};

class Z_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    Z_Block()
    {
        type = 2;
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(1, 1), Block(2, 1)};
        allRotationOptions[1] = {Block(1, 0), Block(1, 1), Block(0, 1), Block(0, 2)};
        heightOfBlock = 2;
        status = allRotationOptions[0];
    }
    void rotateFigure(bool flag) override
    {
        if (flag)
        {
            rotationStatus++;
            if (rotationStatus > 1)
                rotationStatus = 0;

            if(rotationStatus == 0)
                heightOfBlock = 2;
            else
                heightOfBlock = 3;
        }
        else
        {
            rotationStatus--;
            if(rotationStatus < 0)
                rotationStatus = 1;
        }
        status = allRotationOptions[rotationStatus];
    }
    ~Z_Block() override {};
};

class T_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    T_Block()
    {
        type = 3;
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(1, 1)};
        allRotationOptions[1] = {Block(1, 0), Block(1, 1), Block(0, 1), Block(1, 2)};
        allRotationOptions[2] = {Block(1, 0), Block(0, 1), Block(1, 1), Block(2, 1)};
        allRotationOptions[3] = {Block(0, 0), Block(0, 1), Block(0, 2), Block(1, 1)};
        status = allRotationOptions[0];
        heightOfBlock = 2;
    }
    void rotateFigure(bool flag) override
    {
        if (flag)
        {
            rotationStatus++;
            if (rotationStatus > 3)
                rotationStatus = 0;

            if (rotationStatus == 0 || rotationStatus == 3)
                heightOfBlock = 2;
            else
                heightOfBlock = 3;
        }
        else
        {
            rotationStatus--;
            if(rotationStatus < 0)
                rotationStatus = 3;

            if (rotationStatus == 0 || rotationStatus == 3)
                heightOfBlock = 2;
            else
                heightOfBlock = 3;
        }
        status = allRotationOptions[rotationStatus];
    }
    ~T_Block() override {};
};

class S_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    S_Block()
    {
        type = 4;
        allRotationOptions[0] = {Block(1, 0), Block(2, 0), Block(0, 1), Block(1, 1)};
        allRotationOptions[1] = {Block(0, 0), Block(0, 1), Block(1, 1), Block(1, 2)};
        status = allRotationOptions[0];
        heightOfBlock = 2;
    }
    void rotateFigure(bool flag) override
    {
        if (flag)
        {
            rotationStatus++;
            if (rotationStatus > 1)
                rotationStatus = 0;

            if(rotationStatus == 0)
                heightOfBlock = 2;
            else
                heightOfBlock = 3;
        }
        else
        {
            rotationStatus--;
            if(rotationStatus < 0)
                rotationStatus = 1;
        }
        status = allRotationOptions[rotationStatus];
    }
    ~S_Block() override {};
};

class L_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    L_Block()
    {
        type = 5;
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(0, 1)};
        allRotationOptions[1] = {Block(0, 0), Block(1, 0), Block(1, 1), Block(1, 2)};
        allRotationOptions[2] = {Block(0, 1), Block(1, 1), Block(2, 1), Block(2, 0)};
        allRotationOptions[3] = {Block(0, 0), Block(0, 1), Block(0, 2), Block(1, 2)};
        status = allRotationOptions[0];
        heightOfBlock = 3;
    }
    void rotateFigure(bool flag) override
    {
        if (flag)
        {
            rotationStatus++;
            if (rotationStatus > 3)
                rotationStatus = 0;

            if (rotationStatus == 0 || rotationStatus == 3)
                heightOfBlock = 3;
            else
                heightOfBlock = 2;
        }
        else
        {
            rotationStatus--;
            if(rotationStatus < 0)
                rotationStatus = 3;

            if (rotationStatus == 0 || rotationStatus == 3)
                heightOfBlock = 3;
            else
                heightOfBlock = 2;
        }
        status = allRotationOptions[rotationStatus];
    }
    ~L_Block() override {};
};

class I_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    I_Block()
    {
        type = 6;
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(3, 0)};
        allRotationOptions[1] = {Block(0, -3), Block(0, -2), Block(0, -1), Block(0, 0)};
        status = allRotationOptions[0];
        heightOfBlock = 4;
    }
    void rotateFigure(bool flag) override
    {
        if (flag)
        {
            rotationStatus++;
            if (rotationStatus > 1)
                rotationStatus = 0;

            if(rotationStatus == 0)
                heightOfBlock = 4;
            else
                heightOfBlock = 1;
        }
        else
        {
            rotationStatus--;
            if(rotationStatus < 0)
                rotationStatus = 1;
        }
        status = allRotationOptions[rotationStatus];
    }
    ~I_Block() override {};
};

class O_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    O_Block()
    {
        type = 7;
        allRotationOptions[0] = {Block(0, 0), Block(0, 1), Block(1, 0), Block(1, 1)};
        rotationStatus = 0;
        status = allRotationOptions[0];
        heightOfBlock = 2;
    }
    void rotateFigure(bool flag) override
    {

    }
    ~O_Block() override {};
};

#endif //TETRIS_FIGURE_H