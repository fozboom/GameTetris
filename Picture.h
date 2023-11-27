#ifndef TETRIS_PICTURE_H
#define TETRIS_PICTURE_H
#include "Text.h"
#include "SFML/Graphics.hpp"

struct Picture: public Text
{
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    float x_coordinate;
    float y_coordinate;
    Picture() = delete;
    explicit Picture(std::string fileName, float x, float y) : x_coordinate(x), y_coordinate(y),Text("./fonts/D.ttf")
    {
        image.loadFromFile(fileName);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }

    virtual void setPosition (float x, float y)
    {
        x_coordinate = x;
        y_coordinate = y;
        sprite.setPosition(x, y);
    }

    virtual void draw(sf::RenderWindow& window)
    {
        setPosition(x_coordinate, y_coordinate);
        window.draw(sprite);
    }

    float getPositionX () const {return x_coordinate;}
    float getPositionY () const {return y_coordinate;}

    void updateSprite(std::string fileName)
    {
        image.loadFromFile(fileName);

        texture.loadFromImage(image);
        sprite.setTexture(texture);


    }
};

struct PlayerInfo
{
    std::string nickName;
    int score;

public:
    PlayerInfo& operator = (const PlayerInfo& obj)
    {
        this->score = obj.score;
        this->nickName = std::move(obj.nickName);
        return *this;
    }
    PlayerInfo(std::string name = "", int _score = 0): nickName(std::move(name)), score(_score) {};
};


#endif //TETRIS_PICTURE_H
