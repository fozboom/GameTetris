#include "Text.h"

Text::Text(const std::string& _someText, std::string& fontName, int size, int x, int y): x_pos(x), y_pos(y)
{
    // Загрузить файл шрифта
    font.loadFromFile(fontName);
    text.setFont(font);                     // Установить шрифт текста
    text.setCharacterSize(size);            // Установить размер текста
    text.setFillColor(sf::Color::White);    // Установить цвет текста
    someText = std::move(_someText);        // Назначить текстовую строку
    text.setString(someText);               // Присвоить строку тексту для отображения
}

// Конструктор класса Text с 2-мя аргументами размера и выбора
Text::Text(int size, bool sel, std::string fontName)
{
    font.loadFromFile(fontName);      // Загрузить файл шрифта
    text.setFont(font);               // Установить шрифт текста
    text.setCharacterSize(size);      // Установить размер текста
    text.setFillColor(sf::Color(20,122,122));  // Установить цвет текста
    text.setPosition(670,420);            // Установить позицию текста
    isSelected = sel;                 // Установить выбор текста
    if (sel)
    {
        text.setString("|");          // Если выбрано, установить строку на "|"
    }
    else
        text.setString("");           // В противном случае установить пустую строку
}

// Конструктор класса Text с одним аргументом имени шрифта
Text::Text(std::string fontName)
{
    font.loadFromFile(fontName);      // Загрузить файл шрифта
    text.setFont(font);               // Установить шрифт текста
    text.setCharacterSize(48);        // Установить размер текста
    text.setFillColor(sf::Color::White);    // Установить белый цвет текста
    x_pos = 240;                      // Установить позицию X
    y_pos = 530;                      // Установить позицию Y
}

// Обработка ввода пользователем
void Text::inputLogic(int charTyped)
{
    // Если символ введенный пользователем не равен ключам DELETE, ESCAPE, или ENTER
    if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY)
    {
        txt << static_cast<char>(charTyped);  // Добавить символ в поток текста
    }
    else if (charTyped == DELETE_KEY)            // Если пользователь нажал клавишу DELETE,
    {
        if(txt.str().length() > 0)               // и длина строки больше 0,
        {
            deleteLastChar();                     // удалить последний символ
        }
    }
    text.setString(txt.str() + "|");             // Установить строку текста, добавив курсор (|) в конец
}

// Удалить последний символ из текста
void Text::deleteLastChar()
{
    std::string t = txt.str();               // Получить текущий текст
    std::string  newT = "";                  // Создать новую пустую строку
    for (int i = 0; i < t.length() - 1; ++i) // Для каждого символа в текущем тексте, кроме последнего,
    {
        newT += t[i];                        // Добавить символ в новую строку
    }
    txt.str("");                             // Очистить текущий текст
    txt << newT;                             // Установить новый текст как текущий
    text.setString(txt.str());                // Установить новый текст в текст для отображения
}

// Установить строку как число
void Text::setStrAsNumber(float num)
{
    // Преобразовать число в строку и установить как текущий текст
    someText = std::to_string(static_cast<int>(num));
    text.setString(someText);               // Установить текст для отображения
}

// Рисуем текст
void Text::draw(sf::RenderWindow& window)
{
    window.draw(text);  // Нарисовать текст в окне
}

// Отрисовка числа
void Text::drawNumber(sf::RenderWindow& window, int number)
{
    setStrAsNumber(number);  // устанавливаем строку как число
    // Меняем позицию текста, основываясь на количестве цифр в числе
    if (number > 9 && number < 100)
    {
        x_pos = 230;
    }
    else if (number > 99 && number < 1000)
    {
        x_pos = 220;
    }
    text.setPosition(x_pos, y_pos);
    window.draw(text);
}

// Функции для установки текста, позиции и размера текста
void Text::setString(std::string str)
{
    text.setString(str);
}
void Text::setPosition(float x, float y)
{
    text.setPosition(x, y);
}
void Text::setCharacterSize(int size)
{
    text.setCharacterSize(size);
}

// Установить ограничение на длину текста
void Text::setLimit(bool x)
{
    hasLimit = x;
}
void Text::setLimit(bool x, int lim)
{
    hasLimit = x;
    limit = lim;
}

// Установить статус выбора текста
void Text::setSelected(bool sel)
{
    isSelected = sel;
    if(!sel)
    {
        std::string t = txt.str();
        std::string  newT = "";
        for (int i = 0; i < t.length() - 1; ++i)
        {
            newT += t[i];
        }
        text.setString(newT);
    }
}

// Вернуть текущий введенный текст
std::string Text::getString()
{
    return txt.str();
}

// Обрабатывает события ввода после проверки на выбор и лимит символов
void Text::typeOn(sf::Event& event, sf::RenderWindow& window)
{
    if(isSelected)
    {
        int charTyped = event.text.unicode;
        if (charTyped < 128) // Если символ входит в диапазон ASCII
        {
            if (hasLimit)  // Если установлено ограничение,
            {
                // и текущий текст короче или равен лимиту
                if(txt.str().length() < limit)
                {
                    inputLogic(charTyped);  // Обработать введенный символ
                }
                else if(txt.str().length() >= limit && charTyped == DELETE_KEY) // Если текущий текст равен или превышает лимит,
                {                                                               // и был введен символ удаления,
                    deleteLastChar();  // Удалить последний символ
                }
            }
            else
            {
                // Если ограничение не установлено
                inputLogic(charTyped);  // Обработать введенный символ
            }
        }
    }
}