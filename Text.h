#ifndef TETRIS_TEXT_H
#define TETRIS_TEXT_H
#include "header.h"
#include <sstream>

class Text
{
protected:
    std::string someText;
    sf::Font font;
    sf::Text text;
public:

    explicit Text(const std::string& _someText = "")
    {
        font.loadFromFile("ZCOOLQingKeHuangYou-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setString(someText);
        someText = _someText;
    }

    virtual void setPositionNearTheSprite (my_Sprite& spr, float x, float y)
    {
        text.setPosition(spr.getPositionX() + x, spr.getPositionY() + y);
    }

    void setStrAsNumber (float num)
    {
        std::ostringstream number;
        number << num;

        text.setString(number.str());
    }

    void setString (std::string str)
    {
        text.setString(str);
    }

    virtual void setPosition(float x, float y)
    {
        text.setPosition(x, y);
    }

    void setCharacterSize (int size)
    {
        text.setCharacterSize(size);
    }

    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(text);
    }
};


#endif //TETRIS_TEXT_H
