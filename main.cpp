#include "Game.h"

void showMenu(sf::RenderWindow& window)
{
    my_Sprite menuImage("menu.png");
    my_Sprite buttonStart("buttonStart.png");
    my_Sprite buttonResume("buttonResume.png");
    my_Sprite buttonExit("buttonExit.png");

    int isMenu = true;
    int typeOfMenu = 0;
    while(isMenu)
    {
        window.clear();

        if (sf::IntRect(579, 233, 280, 125).contains(sf::Mouse::getPosition(window)))
        {
            typeOfMenu = 1;
        }
        else if (sf::IntRect(579, 395, 280, 125).contains(sf::Mouse::getPosition(window)))
        {
            typeOfMenu = 2;
        }
        else if (sf::IntRect(579, 554, 280, 125).contains(sf::Mouse::getPosition(window)))
        {
            typeOfMenu = 3;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (typeOfMenu == 1){isMenu = false;}
            if (typeOfMenu == 2) {isMenu = false;}
            if (typeOfMenu == 3) { return;}

        }
        if (typeOfMenu == 0)
            window.draw(menuImage.sprite);
        else if (typeOfMenu == 1)
            window.draw(buttonStart.sprite);
        else if (typeOfMenu == 2)
            window.draw(buttonResume.sprite);
        else window.draw(buttonExit.sprite);
        window.display();
    }
}
int main()
{

    Game game;
    //game.writeFileBestPlayers("BestPlayersInfo.txt");
    GameMenu many;

    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetris", sf::Style::Fullscreen);
    showMenu(window);
    sf::Clock timer;
    float pause = 0.27f;
    int key = 0;
    while (window.isOpen())
    {

        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //game.keyPressCheck(event, key, window);
            if(many.getIsMenu())
                many.keyPressCheck(event);
        }
//        game.fallingFigure(timer, pause);
//        game.buttonAction(key);
//        game.lineFilled();
//        if(game.gameOver())
//        {
//            std::cout << "Finish";
//            exit(EXIT_SUCCESS);
//        }
        window.clear();
        if(many.getIsMenu())
            many.showMenu(window);
        //game.showMenu(window);
//        game.draw(window);
//       game.showBestPlayersBlock(window);
        window.display();

    }

    return 0;
}