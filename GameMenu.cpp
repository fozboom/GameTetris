#include "GameMenu.h"
#include "Game.h"

GameMenu::GameMenu():
        mainMenu("images/mainMenu.png", 0, 0),
        selectedMenuOption(0), key(0), isMenu(true)
{
    buttonStart = new Button("Start", 286,127,"images/buttonStart.png", 579,233);
    buttonResume = new Button("Resume", 286,127,"images/buttonResume.png", 579,395);
    buttonExit = new Button("Exit", 286, 127, "images/buttonExit.png",579, 554);
}

GameMenu::~GameMenu() {
    delete buttonStart;
    delete buttonResume;
    delete buttonExit;
}

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
    window.draw(mainMenu.sprite);
    window.draw(buttonStart->sprite);
    window.draw(buttonResume->sprite);
    window.draw(buttonExit->sprite);
    buttonAction(game);
    if (selectedMenuOption == 0)
    {
        buttonStart->updateSprite("images/selectedStart.png");
        buttonResume->updateSprite("images/buttonResume.png");
        buttonExit->updateSprite("images/buttonExit.png");
    }
    else if (selectedMenuOption == 1)
    {
        buttonStart->updateSprite("images/buttonStart.png");
        buttonResume->updateSprite("images/selectedResume.png");
        buttonExit->updateSprite("images/buttonExit.png");
    }
    else
    {
        buttonStart->updateSprite("images/buttonStart.png");
        buttonResume->updateSprite("images/buttonResume.png");
        buttonExit->updateSprite("images/selectedExit.png");
    }

}

void GameMenu::buttonAction(Game& game)
{
    if (key == 1)
    {
        selectedMenuOption--;
        if (selectedMenuOption < 0)
            selectedMenuOption = 2;
        buttonResume->playMusic();
    }
    if (key == 2)
    {
        selectedMenuOption++;
        if (selectedMenuOption > 2)
            selectedMenuOption = 0;
        buttonResume->playMusic();
    }
    if (key == 3)
    {
        buttonResume->playMusic();
        if (selectedMenuOption == 0)
            isMenu = false;
        else if (selectedMenuOption == 1)
        {
            game.loadGameFromFile("Game");
            isMenu = false;
        }
        else
        {

            exit(EXIT_SUCCESS);
        }
    }
    key = 0;
}

bool GameMenu::getIsMenu() const
{
    return isMenu;
}
void GameMenu::setIsMenu(bool x)
{
    isMenu = x;
}


