#include "Picture.h"

Picture::Picture(std::string fileName, float x, float y) : x_coordinate(x), y_coordinate(y),Text("./fonts/D.ttf")
{
    image.loadFromFile(fileName);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

void Picture::setPosition (float x, float y)
{
    x_coordinate = x;
    y_coordinate = y;
    sprite.setPosition(x, y);
}

void Picture::draw(sf::RenderWindow& window)
{
    setPosition(x_coordinate, y_coordinate);
    window.draw(sprite);
}

float Picture::getPositionX () const
{
    return x_coordinate;
}

float Picture::getPositionY () const
{
    return y_coordinate;
}

void Picture::updateSprite(std::string fileName)
{
    image.loadFromFile(fileName);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}