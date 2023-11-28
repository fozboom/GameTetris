#include "Button.h"

Button::Button(std::string _someText, float w, float h, std::string fileName, float x, float y) :
        Picture(fileName, x , y), width(w), height(h), isPressed(false)
{
    buffer.loadFromFile("music/click.ogg");
    sound.setBuffer(buffer);
    sprite.setPosition(x,y);
}

void Button::draw(sf::RenderWindow &window)
{
    sprite.setPosition(x_coordinate, y_coordinate);
    window.draw(sprite);
}

float Button::getWidth()
{
    return width;}
float Button::getHeight()
{
    return height;}
void Button::playMusic()
{
    sound.play();}
bool Button::getIsPressed()
{
    return isPressed;
}
void Button::setIsPressed(bool val)
{
    isPressed = val;
}







