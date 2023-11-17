#include "Game.h"

bool startGame(GameMenu& menu);
void gameRunning(GameMenu& menu);

int main()
{
    GameMenu menu;
    gameRunning(menu);

    return 0;
}

bool startGame(GameMenu& menu)
{
    Game game;
    //game.writeFileBestPlayers("BestPlayersInfo.txt");
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetris", sf::Style::Fullscreen);
    if(game.drawWindow(window, menu)) return true;
    return false;
}

void gameRunning(GameMenu& menu)
{
    if(startGame(menu)){gameRunning(menu);}
}


