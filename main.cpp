#include "Game.h"
#include <filesystem>
bool startGame(GameMenu& menu);
void gameRunning(GameMenu& menu);

int main()
{
    std::filesystem::path exePath = std::filesystem::absolute(std::filesystem::path("/Users/fozboom/CLionProjects/GameTetris/cmake-build-debug/"));
    std::filesystem::current_path(exePath.parent_path());

    GameMenu menu;
    gameRunning(menu);

    return 0;
}

bool startGame(GameMenu& menu)
{
    Game game;
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetris", sf::Style::Fullscreen);
    if(game.drawWindow(window, menu)) return true;
    return false;
}

void gameRunning(GameMenu& menu)
{
    if(startGame(menu)){gameRunning(menu);}
}


