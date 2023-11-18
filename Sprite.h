#ifndef TETRIS_SPRITE_H
#define TETRIS_SPRITE_H
#include "SFML/Graphics.hpp"

struct my_Sprite
{
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    float x_coordinate;
    float y_coordinate;
    my_Sprite() = delete;
    explicit my_Sprite(std::string fileName, float x, float y) : x_coordinate(x), y_coordinate(y)
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
};


#endif //TETRIS_SPRITE_H
