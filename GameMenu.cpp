#include "GameMenu.h"
#include "Game.h"

GameMenu::GameMenu(): buttonStart("images/buttonStart.png", 0, 0),
buttonResume("images/buttonResume.png",0, 0), buttonExit("images/buttonExit.png",0, 0), typeOfMenu(0), key(0), isMenu(true){}

void GameMenu::keyPressCheck(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            key = 1;
        }
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            key = 2;
        }
        if (event.key.code == sf::Keyboard::Enter)
        {
            key = 3;
        }
    }
}



void GameMenu::showMenu(sf::RenderWindow& window, Game& game)
{

    buttonAction(game);
    if (typeOfMenu == 0)
        window.draw(buttonStart.sprite);
    else if (typeOfMenu == 1)
        window.draw(buttonResume.sprite);
    else window.draw(buttonExit.sprite);

}

void GameMenu::buttonAction(Game& game)
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
        else if (typeOfMenu == 1)
        {
            game.loadGameFromFile("Game");
            game.setIsLoadFromFile(true);
            isMenu = false;
        }
        else
            exit(EXIT_SUCCESS);
    }
    key = 0;
}


