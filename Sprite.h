#ifndef TETRIS_SPRITE_H
#define TETRIS_SPRITE_H
#include "SFML/Graphics.hpp"

struct my_Sprite
{
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    my_Sprite() = delete;
    explicit my_Sprite(const char * fileName)
    {
        image.loadFromFile(fileName);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
};

struct PlayerInfo
{
    char nickName [11];
    int scope;
};


#endif //TETRIS_SPRITE_H
