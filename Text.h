#ifndef TETRIS_TEXT_H
#define TETRIS_TEXT_H

#include "header.h"    // Включить другие необходимые заголовки
#include <sstream>     // Включить заголовочный файл для работы со строковыми потоками

// Макросы для определения клавиш (по ASCII-коду)
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

// Класс Text для отображения и обработки текста
class Text
{
protected:
    std::string someText;                // Стандартная строка для работы с текстом
    sf::Font font;                       // Шрифт текста
    sf::Text text;                       // Текст для отображения его на экране
    std::ostringstream txt;              // Строковый поток для работы с текстом
    bool isSelected = true;              // Проверка, выбран ли текст
    bool hasLimit = true;                // Ограничение на количество символов
    float x_pos;                         // X позиция текста
    float y_pos;                         // Y позиция текста
    int limit = 10;                      // Лимит символов для текста

public:
    // Контструкторы Text
    explicit Text(const std::string& _someText, std::string& fontName, int size, int x, int y);
    Text (int size, bool sel, std::string fontName);
    Text (std::string fontName);

    // Методы для обработки текста и его отображения
    void inputLogic(int charTyped);              // Обрабатывает вводимые символы
    void deleteLastChar();                       // Удалить последний символ
    void setStrAsNumber(float num);              // Установить строку в виде числа
    virtual void draw(sf::RenderWindow& window); // Отрисовывает текст в окне
    void drawNumber(sf::RenderWindow& window, int number); // Рисует числа в окне
    void setString(std::string str);             // Установить строку
    virtual void setPosition(float x, float y);  // Установить позицию текста
    void setCharacterSize(int size);             // Установить размер символа
    void setLimit(bool x);                       // Установить флаг имеет ли строка лимит 
    void setLimit(bool x, int lim);              // Установить флаг и максимум символов 
    void setSelected(bool sel);                  // Выбрано ли текстовое поле
    std::string getString();                     // Получить строку
    void typeOn(sf::Event& event, sf::RenderWindow& window); // Обрабатывает события ввода данных от пользователя

};

#endif // TETRIS_TEXT_H