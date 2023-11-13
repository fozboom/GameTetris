#include "Game.h"
int main()
{


    Game game;

    //game.writeFileBestPlayers("BestPlayersInfo.txt");


    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetris", sf::Style::Fullscreen);


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

            game.keyPressCheck(event, key, window);
        }

        game.fallingFigure(timer, pause);
        game.buttonAction(key);
        game.lineFilled();
        if(game.gameOver())
        {
            std::cout << "Finish";
            exit(EXIT_SUCCESS);
        }
        window.clear();

        //game.showMenu(window);
        game.draw(window);
       //game.showBestPlayersBlock(window);
        window.display();

    }

    return 0;
}