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
    explicit Text(const std::string& _someText, std::string& fontName, int size, int x, int y);
    Text (int size, bool sel, std::string fontName);
    Text (std::string fontName);

    void inputLogic (int charTyped);
    void deleteLastChar ();
    void setStrAsNumber (float num);
    virtual void draw(sf::RenderWindow& window);
    void drawNumber (sf::RenderWindow& window, int number);
    void setString (std::string str);
    virtual void setPosition(float x, float y);
    void setCharacterSize (int size);
    void setLimit(bool x);
    void setLimit (bool x, int lim);
    void setSelected(bool sel);
    std::string getString();
    void typeOn (sf::Event& event, sf::RenderWindow& window);

};

#endif //TETRIS_TEXT_H