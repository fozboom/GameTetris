#include "Game.h"

void showMenu(sf::RenderWindow& window);
bool startGame(GameMenu& menu)
{
    Game game;
    //game.writeFileBestPlayers("BestPlayersInfo.txt");

    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetris", sf::Style::Fullscreen);

    sf::Clock timer;
    float pause = 0.27f;
    int key = 0;
    bool isPaused = true;
    while (window.isOpen())
    {

        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(menu.getIsMenu())
                menu.keyPressCheck(event);
            else
            {
                game.keyPressCheck(event, key, window);

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::R)
                    {
                        return true;
                    }
                    if (event.key.code == sf::Keyboard::Q)
                    {
                        return false;
                    }
                    if (event.key.code == sf::Keyboard::Space )
                    {
                        while (window.waitEvent(event))
                        {
                            if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)||
                                    (sf::IntRect(1104, 619, 120, 120).contains(sf::Mouse::getPosition(window))
                                     && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                                break;
                        }
                    }
                }
                if (sf::IntRect(1104, 619, 120, 120).contains(sf::Mouse::getPosition(window))
                 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    while (window.waitEvent(event))
                    {
                        if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)||
                           (sf::IntRect(1104, 619, 120, 120).contains(sf::Mouse::getPosition(window))
                            && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                            break;
                    }
                }
                if (sf::IntRect(1109, 483, 110, 110).contains(sf::Mouse::getPosition(window))
                && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                   return true;
                }



            }
        }

        window.clear();
        if(menu.getIsMenu())
            menu.showMenu(window);
        else
        {
            game.fallingFigure(timer, pause);
            game.buttonAction(key);

            if(game.gameOver())
            {
                std::cout << "Finish";
                exit(EXIT_SUCCESS);
            }
            game.draw(window);
            game.showScore(window);
            game.showBestPlayersBlock(window);
        }

        window.display();

    }
}

void gameRunning(GameMenu& menu)
{
    if(startGame(menu)){gameRunning(menu);}
}

int main()
{
    GameMenu menu;
    gameRunning(menu);
    return 0;
}