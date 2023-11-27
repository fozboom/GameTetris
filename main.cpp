#include "Game.h"
#include <filesystem>

[[noreturn]] void gameRunning(GameMenu& menu)
{
    while (true)
    {
        Game game;
        sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetris", sf::Style::Fullscreen);
        game.processGameCycle(window, menu);
    }
}


int main()
{
    std::filesystem::path exePath = std::filesystem::absolute(std::filesystem::path("/Users/fozboom/CLionProjects/GameTetris/cmake-build-debug/"));
    std::filesystem::current_path(exePath.parent_path());

    GameMenu menu;
    gameRunning(menu);
}



