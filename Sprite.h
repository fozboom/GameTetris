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
    explicit my_Sprite(const char * fileName) : x_coordinate(0), y_coordinate(0)
    {
        image.loadFromFile(fileName);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }

    void setPosition (int x, int y)
    {
        x_coordinate = x;
        y_coordinate = y;
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    }

    float getPositionX () const {return x_coordinate;}
    float getPositionY () const {return y_coordinate;}
};

struct PlayerInfo
{
    char nickName [11];
    int score;

public:
    PlayerInfo& operator = (const PlayerInfo& obj)
    {
        this->score = obj.score;
        strcpy(this->nickName, obj.nickName);
        return *this;
    }
};


#endif //TETRIS_SPRITE_H
