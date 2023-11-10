#ifndef TETRIS_BUTTON_H
#define TETRIS_BUTTON_H
#include "header.h"

class Button {
private:
    sf::Image buttonImage;
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    bool isPressed;

public:

    void press() {isPressed = true;}

    void release() {isPressed = false;}

    bool isButtonPressed() const {return isPressed;}

    const sf::Sprite& getSprite() const {return buttonSprite;}
};


#endif //TETRIS_BUTTON_H
