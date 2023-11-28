#ifndef TETRIS_PICTURE_H
#define TETRIS_PICTURE_H

#include "SFML/Graphics.hpp"
#include "Text.h"
#include "PlayerInfo.h"


struct Picture: public Text
{
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    float x_coordinate;
    float y_coordinate;

    Picture() = delete;
    explicit Picture(std::string fileName, float x, float y);

    virtual void setPosition (float x, float y) override;
    virtual void draw(sf::RenderWindow& window) override;
    float getPositionX () const;
    float getPositionY () const;
    void updateSprite(std::string fileName);
};

#endif //TETRIS_PICTURE_H