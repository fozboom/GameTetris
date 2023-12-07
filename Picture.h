#ifndef TETRIS_PICTURE_H
#define TETRIS_PICTURE_H

#include "SFML/Graphics.hpp"
#include "Text.h"
#include "PlayerInfo.h"

// Структура Picture используется для создания изображения, наследуется от Text
struct Picture: public Text
{
    sf::Image image; // Внутренняя переменная для хранения изображения
    sf::Texture texture; // Текстура изображения
    sf::Sprite sprite; // Спрайт, который выводится на экран
    float x_coordinate; // Координата x спрайта
    float y_coordinate; // Координата y спрайта

    Picture() = delete; // Запрещаем конструктор по умолчанию
    explicit Picture(std::string fileName, float x, float y); // Конструктор, принимающий имя файл и координаты

    virtual void setPosition (float x, float y) override; // Метод установки позиции спрайта
    virtual void draw(sf::RenderWindow& window) override; // Метод отрисовки спрайта в окне
    float getPositionX () const; // Геттер для координаты x
    float getPositionY () const; // Геттер для координаты y
    void updateSprite(std::string fileName); // Метод обновления спрайта
};

#endif //TETRIS_PICTURE_H