#include "Game.h"


int generateRandomNumber(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(gen);
}

void Game::keyPressCheck(sf::Event& event, int& key, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left)
        {
            key = 1;
        }if (event.key.code == sf::Keyboard::Right)
        {
            key = 2;
        }
        if (event.key.code == sf::Keyboard::Up)
        {
            key = 3;
        }if (event.key.code == sf::Keyboard::Down)
        {
            key = 4;
        }

        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }


}

Game::Game():background("back.png"), oneBlock("color_cubes.png"), blockNextFigure("blockNextFigure.png"), figures(getAllFigures()), field()
{
    currentFigure = getRandomFigure();
    nextFigure = getRandomFigure();
    blockNextFigure.sprite.setScale(    0.50, 0.50);
    background.sprite.setScale(1300, 1500);

}

Figure* Game::getRandomFigure()
{
    if(figures.empty())
    {
        figures = {new J_Block(), new Z_Block(), new T_Block(), new S_Block(), new L_Block(), new I_Block(), new O_Block()};
    }
    int randomIndex = generateRandomNumber(0, 6);
    Figure* fig = figures[randomIndex];
    figures.erase(figures.begin() + randomIndex);
    return fig;
}

void Game::draw(sf::RenderWindow& window)
{
//    window.draw(background.sprite);
    drawGrid(window);
    //blockNextFigure.sprite.setPosition(30*CELL_SIZE, 8*CELL_SIZE);
    //window.draw(blockNextFigure.sprite);
    currentFigure->drawFigure(window);
    figures = getAllFigures();

}

std::vector<Figure*> Game::getAllFigures()
{
    return {new J_Block(), new Z_Block(), new T_Block(), new S_Block(), new L_Block(), new I_Block(), new O_Block()};
}

bool Game::boundariesIsBroken()
{
    std::vector<Block> object = currentFigure->newCondition();
    for (auto & i : object)
    {
        if (i.x< 0 || i.x > WIDTH - 1 || field.getGameBoard(i.y, i.x) != 0 || i.y > HEIGHT - 1)
            return true;
    }
    return false;
}

void Game::isLocked()
{
    std::vector<Block> object = currentFigure->newCondition();
    for (Block item: object)
    {
        field.setGameBoard(item.y, item.x, currentFigure->getColor());
    }
    currentFigure = nextFigure;
    nextFigure = getRandomFigure();
}

void Game::drawGrid(sf::RenderWindow& window)
{
    std::vector<Block> tmp = currentFigure->newCondition();


    field.drawGameBoard(window);

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (field.getGameBoard(i,j) != 0)
            {
                oneBlock.sprite.setTextureRect(sf::IntRect((field.getGameBoard(i, j) - 1) * CELL_SIZE, 0, CELL_SIZE , CELL_SIZE) );
                oneBlock.sprite.setPosition((j*CELL_SIZE+466), (i*CELL_SIZE+166));
                window.draw(oneBlock.sprite);
            }
        }
    }
}

void Game::buttonAction(int &key, Game& game)
{
    if (key == 1)
    {
        game.currentFigure->move(-1, 0);
        if(game.boundariesIsBroken())
            game.currentFigure->move(1, 0);
    }
    if (key == 2)
    {
        game.currentFigure->move(1, 0);
        if(game.boundariesIsBroken())
            game.currentFigure->move(-1, 0);
    }
    if (key == 3)
    {
        game.currentFigure->rotateTetromino(true);
        if(game.boundariesIsBroken())
            game.currentFigure->rotateTetromino(false);
    }
    if (key == 4)
    {
        game.currentFigure->move(0, 1);
        if(game.boundariesIsBroken())
            game.currentFigure->move(0, -1);
    }
    key = 0;
}

void Game::fallingFigure(sf::Clock& timer, float pause, Game& game)
{
    if (timer.getElapsedTime().asSeconds() >= pause) {
        timer.restart();
        game.currentFigure->move(0,1);
        if(game.boundariesIsBroken())
        {
            game.currentFigure->move(0, -1);
            game.isLocked();
        }
    }
}

bool Game::gameOver()
{
    std::vector<Block> object = currentFigure->newCondition();
    for (Block item: object)
        if (boundariesIsBroken() && (item.y == 0))
            return true;
    return false;
}

void Game::lineFilled()
{
    bool flag = true;
    for (int i = HEIGHT - 1; i >= 0; --i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (field.getGameBoard(i, j) == 0)
            {
                flag =  false;
                break;
            }
        }
        if (flag)
        {
            deleteLine(i);
        }
        flag = true;
    }
}

void Game::deleteLine(int k)
{
    for (int i = k; i > 0; --i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            field.setGameBoard(i,j,field.getGameBoard(i-1, j));

        }
    }
    for (int j = 0; j < WIDTH; ++j)
        field.setGameBoard(0, j, 0);

}
