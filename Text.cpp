#include "Text.h"

Text::Text(const std::string& _someText, std::string& fontName, int size, int x, int y): x_pos(x), y_pos(y)
{
    font.loadFromFile(fontName);
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    someText = std::move(_someText);
    text.setString(someText);
}

Text::Text(int size, bool sel, std::string fontName)
{
    font.loadFromFile(fontName);
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color(20,122,122));
    text.setPosition(670,420);
    isSelected = sel;
    if (sel)
    {
        text.setString("|");
    }
    else
        text.setString("");
}

Text::Text(std::string fontName)
{
    font.loadFromFile(fontName);
    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
    x_pos = 240;
    y_pos = 530;
}

void Text::inputLogic(int charTyped)
{
    if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY)
    {
        txt << static_cast<char>(charTyped);
    }
    else if (charTyped == DELETE_KEY)
    {
        if(txt.str().length() > 0)
        {
            deleteLastChar();
        }
    }
    text.setString(txt.str() + "|");
}

void Text::deleteLastChar()
{
    std::string t = txt.str();
    std::string  newT = "";
    for (int i = 0; i < t.length() - 1; ++i)
    {
        newT += t[i];
    }
    txt.str("");
    txt << newT;
    text.setString(txt.str());
}

void Text::setStrAsNumber(float num)
{
    someText = std::to_string(static_cast<int>(num));
    text.setString(someText);
}

void Text::draw(sf::RenderWindow& window)
{
    window.draw(text);
}

void Text::drawNumber(sf::RenderWindow& window, int number)
{
    setStrAsNumber(number);
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

void Text::setLimit(bool x)
{
    hasLimit = x;
}

void Text::setLimit(bool x, int lim)
{
    hasLimit = x;
    limit = lim;
}

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

std::string Text::getString()
{
    return txt.str();
}

void Text::typeOn(sf::Event& event, sf::RenderWindow& window)
{
    if(isSelected)
    {
        int charTyped = event.text.unicode;
        if (charTyped < 128)
        {
            if (hasLimit)
            {
                if(txt.str().length() < limit)
                {
                    inputLogic(charTyped);
                }
                else if(txt.str().length() >= limit && charTyped == DELETE_KEY)
                {
                    deleteLastChar();
                }
            }
            else
                inputLogic(charTyped);
        }
    }
}