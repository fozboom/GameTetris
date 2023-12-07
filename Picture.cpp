#include "Picture.h"

// Конструктор структуры Picture
Picture::Picture(std::string fileName, float x, float y) : x_coordinate(x), y_coordinate(y), Text("./fonts/D.ttf")
{
    image.loadFromFile(fileName); // Загрузка изображения из файла
    texture.loadFromImage(image); // Создание текстуры из изображения
    sprite.setTexture(texture); // Установка текстуры для спрайта
}

// Метод устанавливает позицию спрайта
void Picture::setPosition (float x, float y)
{
    x_coordinate = x;
    y_coordinate = y;
    sprite.setPosition(x, y);
}

// Метод отрисовки спрайта в окне
void Picture::draw(sf::RenderWindow& window)
{
    setPosition(x_coordinate, y_coordinate); // Устанавливаем позицию спрайта
    window.draw(sprite); // Отрисовываем спрайт
}

// Геттеры для координат спрайта
float Picture::getPositionX () const
{
    return x_coordinate;
}

float Picture::getPositionY () const
{
    return y_coordinate;
}

// Метод обновляет спрайт, загрузив новое изображение из файла
void Picture::updateSprite(std::string fileName)
{
    image.loadFromFile(fileName); // Загрузка нового изображения
    texture.loadFromImage(image); // Создание новой текстуры
    sprite.setTexture(texture); // Установка новой текстуры для спрайта
}