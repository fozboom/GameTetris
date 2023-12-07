#ifndef TETRIS_BUTTON_H
#define TETRIS_BUTTON_H

#include "Picture.h"
#include "header.h"
#include <SFML/Audio.hpp>

// Класс Button наследуется от класса Picture.
// Это позволяет создавать кнопки с изображением и звуком.
class Button: public Picture
{
private:
    // Параметры кнопки
    float width;
    float height;

    // Звуковые параметры кнопки
    sf::SoundBuffer buffer;
    sf::Sound sound;

    // Состояние кнопки
    bool isPressed;

public:
    // Конструктор и деструктор
    Button() = delete;
    explicit Button(std::string _someText, float w, float h, std::string fileName, float x, float y);
    ~Button();

    // Функции для работы с кнопкой
    void draw(sf::RenderWindow& window) override;
    float getWidth();
    float getHeight();
    void playMusic();
    bool getIsPressed();
    void setIsPressed(bool val);
};

#endif //TETRIS_BUTTON_H