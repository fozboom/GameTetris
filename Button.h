#ifndef TETRIS_BUTTON_H
#define TETRIS_BUTTON_H
#include "header.h"
#include <SFML/Audio.hpp>

class Button: public Text
{
private:
    float width;
    float height;

    sf::SoundBuffer buffet;
    sf::Sound sound;

    bool isPressed;

    sf::RectangleShape button;

public:
    explicit Button(std::string& _someText, float w = 0, float h = 0);
};


#endif //TETRIS_BUTTON_H
