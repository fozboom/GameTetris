
#include "Figure.h"

Figure::Figure(): cubeImage("color_cubes.png"), type(0), cellSize(30), offsetX(0), offsetY(0)
{
    rotationStatus = generateRandomNumber(0, 3);
    color = generateRandomNumber(1, 8);
}


void Figure::drawFigure(sf::RenderWindow& window)
{
    std::vector<Block> tmp = newCondition();

    cubeImage.sprite.setTextureRect(sf::IntRect((color-1) * cellSize,0,cellSize , cellSize) );
    for (Block item: tmp)
    {
        cubeImage.sprite.setPosition(static_cast<float>(item.x*cellSize +466), static_cast<float>(item.y*cellSize + 166));
        window.draw(cubeImage.sprite);
    }
}

void Figure::move(int x, int y)
{
    this->offsetX += x;
    this->offsetY += y;
}

std::vector<Block> Figure::newCondition()
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

void Figure::rotateTetromino(bool flag)
{
    if (flag)
    {
        rotationStatus++;
        if (rotationStatus > 3)
            rotationStatus = 0;
    }
    else
    {
        rotationStatus--;
        if(rotationStatus < 0)
            rotationStatus = 3;
    }

}


Block::Block(int x, int y)
{
    this->x = x;
    this->y = y;
}



