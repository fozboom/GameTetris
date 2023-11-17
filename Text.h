#ifndef TETRIS_TEXT_H
#define TETRIS_TEXT_H
#include "header.h"
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Text
{
protected:
    std::string someText;
    sf::Font font;
    sf::Text text;
    std::ostringstream txt;
    bool isSelected = true;
    bool hasLimit = true;
    float x_pos;
    float y_pos;
    int limit = 10;
public:

    explicit Text(const std::string& _someText, std::string& fontName, int size, int x, int y): x_pos(x), y_pos(y)
    {
        font.loadFromFile(fontName);
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::White);
        someText = std::move(_someText);
        text.setString(someText);
    }

    Text (int size, bool sel, std::string fontName)
    {
        font.loadFromFile(fontName);
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::White);
        text.setPosition(100,100);
        isSelected = sel;
        if (sel)
        {
            text.setString("Hello");
        }
        else
            text.setString("");
    }

    void inputLogic (int charTyped)
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
        text.setString(txt.str() + "_");
    }

    void deleteLastChar ()
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

    void setStrAsNumber (float num)
    {
        someText = std::to_string(static_cast<int>(num));
        text.setString(someText);
    }

    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(text);
    }

    void drawNumber (sf::RenderWindow& window, int number)
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




    void setLimit(bool x)
    {
        hasLimit = x;
    }

    void setLimit (bool x, int lim)
    {
        hasLimit = x;
        limit = lim;
    }

    void setSelected(bool sel)
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

    std::string getString(){return txt.str();}


    void typeOn (sf::Event& event, sf::RenderWindow& window)
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

       // text.setString(txt.str() + "|");
        text.setPosition(220,220);
        //window.draw(text);
        std::cout << txt.str() << "\n";



    }
};


#endif //TETRIS_TEXT_H
