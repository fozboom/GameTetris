#ifndef TETRIS_BUTTON_H
#define TETRIS_BUTTON_H
#include "header.h"
#include <SFML/Audio.hpp>

class Button: public Picture
{
private:
    float width;
    float height;

    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool isPressed;

public:
    Button() = delete;
    explicit Button(std::string _someText, float w, float h, std::string fileName, float x, float y, std::string fontName, int size, float x_pos, float y_pos);
    void draw(sf::RenderWindow& window) override;
    float getWidth();
    float getHeight();
    void playMusic();
    bool getIsPressed();
    void setIsPressed(bool val);
};


#endif //TETRIS_BUTTON_H
