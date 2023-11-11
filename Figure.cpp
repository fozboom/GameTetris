
#include "Figure.h"

int generateRandomNumber(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(gen);
}

Figure::Figure(): shadowCube("shadow_cube.png"), cubeImage("color_cubes.png"), type(0), cellSize(30), offsetX(6), offsetY(0), distanceToCollision(0)
{
    rotationStatus = 0;
    color = generateRandomNumber(1, 8);
}





void Figure::drawFigure(sf::RenderWindow& window)
{
    std::vector<Block> tmp = newCondition();

    cubeImage.sprite.setTextureRect(sf::IntRect((color-1) * cellSize,0,cellSize , cellSize) );
    shadowCube.sprite.setTextureRect(sf::IntRect((color-1) * cellSize,0,cellSize , cellSize) );
    for (Block item: tmp)
    {
        cubeImage.sprite.setPosition(static_cast<float>(item.x*cellSize +463), static_cast<float>(item.y*cellSize + 167));
        window.draw(cubeImage.sprite);
        if (distanceToCollision >= heightOfBlock)
        {
            shadowCube.sprite.setPosition(static_cast<float>(item.x * cellSize + 463),
                                         static_cast<float>(item.y * cellSize + 167 + distanceToCollision * CELL_SIZE));
            window.draw(shadowCube.sprite);
        }
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



