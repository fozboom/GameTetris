#include "Game.h"
int main()
{
    Game game;


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

        game.fallingFigure(timer, pause, game);
        game.buttonAction(key, game);
        game.lineFilled();
        if(game.gameOver())
        {
            std::cout << "Finish";
            exit(EXIT_SUCCESS);
        }
        window.clear();

        //window.draw(game.backg);
        game.draw(window);
        window.display();

    }

    return 0;
}
