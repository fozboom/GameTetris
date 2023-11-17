//
// Created by Даниель Гнетецкий on 10.11.23.
//

#include "Button.h"

#include <utility>

Button::Button(std::string& _someText, float w, float h) : Text(_someText), width(w), height(h), isPressed(false)
{
    button.setSize(sf::Vector2f(width, height));
    text.setPosition(button.getPosition());
}



