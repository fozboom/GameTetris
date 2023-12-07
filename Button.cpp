#include "Button.h"

// Конструктор кнопки, получает параметры текста, размера, изображения и координат
Button::Button(std::string _someText, float w, float h, std::string fileName, float x, float y) :
        Picture(fileName, x , y), width(w), height(h), isPressed(false)
{
    // Загрузка звука для кнопки
    buffer.loadFromFile("music/click.ogg");
    sound.setBuffer(buffer);

    // Позиционирование кнопки
    sprite.setPosition(x,y);
}

// Отрисовка кнопки
void Button::draw(sf::RenderWindow &window)
{
    sprite.setPosition(x_coordinate, y_coordinate);
    window.draw(sprite);
}

// Функции для получения размеров кнопки
float Button::getWidth()
{
    return width;
}
float Button::getHeight()
{
    return height;
}

// Функция для воспроизведения звука кнопки
void Button::playMusic()
{
    sound.play();
}

// Функции для работы с состоянием кнопки
bool Button::getIsPressed()
{
    return isPressed;
}
void Button::setIsPressed(bool val)
{
    isPressed = val;
}

// Деструктор кнопки
Button::~Button()
{

}