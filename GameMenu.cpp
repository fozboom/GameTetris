#include "GameMenu.h"

GameMenu::GameMenu(): buttonStart("buttonStart.png"),
buttonResume("buttonResume.png"), buttonExit("buttonExit.png"), typeOfMenu(0), key(0), isMenu(true){}

void GameMenu::keyPressCheck(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            key = 1;
        }
        if (event.key.code == sf::Keyboard::S)
        {
            key = 2;
        }
        if (event.key.code == sf::Keyboard::Enter)
        {
            key = 3;
        }
    }
}



void GameMenu::showMenu(sf::RenderWindow& window)
{

    buttonAction();
    if (typeOfMenu == 0)
        window.draw(buttonStart.sprite);
    else if (typeOfMenu == 1)
        window.draw(buttonResume.sprite);
    else window.draw(buttonExit.sprite);

}

void GameMenu::buttonAction()
{
    if (key == 1)
    {
        typeOfMenu--;
        if (typeOfMenu < 0)
            typeOfMenu = 2;
    }
    if (key == 2)
    {
        typeOfMenu++;
        if (typeOfMenu > 2)
            typeOfMenu = 0;
    }
    if (key == 3)
    {
        if (typeOfMenu == 0)
            isMenu = false;
        else
            exit(EXIT_SUCCESS);
    }
    key = 0;
}
