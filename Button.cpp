//
// Created by Даниель Гнетецкий on 10.11.23.
//

#include "Button.h"



Button::Button(std::string _someText, float w, float h, std::string fileName, float x, float y, std::string fontName, int size, float x_pos, float y_pos) :
my_Sprite(fileName, x , y), Text(_someText, fontName, size, x_pos, y_pos), width(w), height(h), isPressed(false)
{

}

void Button::draw(sf::RenderWindow &window)
{
    sprite.setPosition(x_coordinate, y_coordinate);
    window.draw(sprite);

}







