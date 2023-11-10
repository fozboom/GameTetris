#ifndef TETRIS_FIGURE_H
#define TETRIS_FIGURE_H
#pragma once
#include "header.h"

int generateRandomNumber(int a, int b);

class Block
{
public:
    int x;
    int y;
    Block(int x, int y);

};

class Figure
{
protected:
    std::vector <Block> status;
    int rotationStatus;
    int color;
    int cellSize;
    int offsetX;
    int offsetY;
    int heightOfBlock;
    int distanceToCollision;
    my_Sprite cubeImage;
    my_Sprite shadowCube;
    int type;
public:
    Figure();
    int getType() const {return type;}
    int getColor() const {return color;}
    int getRotation()const {return rotationStatus;}
    void setDistanceToCollision(int x){distanceToCollision = x;}
    sf::Sprite& getCubeSprite() {return cubeImage.sprite;}
    void drawFigure(sf::RenderWindow& window);
    void move(int xPos, int yPos);
    std::vector<Block> newCondition ();
    virtual void rotateTetromino (bool flag);
    std::vector<Block>& getStatus(){return status;}
    int get_offset_x() const{return offsetX;}
    int get_offset_y() const{return offsetY;}
};

class J_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    J_Block()
    {
        type = 1;
        allRotationOptions[3] = {Block(1, 0), Block(1, 1), Block(1, 2), Block(0, 2)};
        allRotationOptions[1] = {Block(0, 0), Block(0, 1), Block(1, 1), Block(2, 1)};
        allRotationOptions[2] = {Block(0, 0), Block(1, 0), Block(0, 1), Block(0, 2)};
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(2, 1)};
        status = allRotationOptions[0];
        heightOfBlock = 3;
    }
    void rotateTetromino(bool flag) override
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
    void rotateTetromino(bool flag) override
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
    void rotateTetromino(bool flag) override
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
    void rotateTetromino(bool flag) override
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
};

class L_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    L_Block()
    {
        type = 5;
        allRotationOptions[1] = {Block(0, 0), Block(0, 1), Block(0, 2), Block(1, 2)};
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(0, 1)};
        allRotationOptions[2] = {Block(0, 0), Block(1, 0), Block(1, 1), Block(1, 2)};
        allRotationOptions[3] = {Block(0, 1), Block(1, 1), Block(2, 1), Block(2, 0)};
        status = allRotationOptions[0];
        heightOfBlock = 3;
    }
    void rotateTetromino(bool flag) override
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
};

class I_Block: public Figure
{
private:
    std::map<int, std::vector<Block>> allRotationOptions;
public:
    I_Block()
    {
        type = 6;
        allRotationOptions[1] = {Block(0, 0), Block(0, 1), Block(0, 2), Block(0, 3)};
        allRotationOptions[0] = {Block(0, 0), Block(1, 0), Block(2, 0), Block(3, 0)};
        status = allRotationOptions[0];
        heightOfBlock = 4;
    }
    void rotateTetromino(bool flag) override
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
    void rotateTetromino(bool flag) override
    {

    }
};

#endif //TETRIS_FIGURE_H
