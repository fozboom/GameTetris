#include "Game.h"




void Game::keyPressCheck(sf::Event& event, int& key, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
        {
            key = 1;
        }
        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
        {
            key = 2;
        }
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
        {
            key = 3;
        }
        if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
        {
            key = 4;
        }
        if (event.key.code == sf::Keyboard::Space)
        {
            key = 5;
        }
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }


}

Game::Game():oneBlock("color_cubes.png"), figures(getAllFigures()), field()
{
    currentFigure = getRandomFigure();
    nextFigure = getRandomFigure();
    currentFigure->setDistanceToCollision(distanceToLocked());

}

Figure* Game::getRandomFigure()
{
    if (figures.empty())
    {
        figures.push_back(new J_Block());
        figures.push_back(new Z_Block());
        figures.push_back(new T_Block());
        figures.push_back(new S_Block());
        figures.push_back(new L_Block());
        figures.push_back(new I_Block());
        figures.push_back(new O_Block());
    }

    int randomIndex = generateRandomNumber(0, static_cast<int>(figures.size()) - 1);
    Figure* fig = figures[randomIndex];


    figures.erase(figures.begin() + randomIndex);

    return fig;
}

void Game::draw(sf::RenderWindow& window)
{
    drawGrid(window);
    currentFigure->setDistanceToCollision(distanceToLocked());
    currentFigure->drawFigure(window);
    drawNextFigureBlock(window);
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
                oneBlock.sprite.setPosition(static_cast<float>(j*CELL_SIZE+466), static_cast<float>(i*CELL_SIZE+166));
                window.draw(oneBlock.sprite);
            }
        }
    }
}

void Game::buttonAction(int &key)
{
    if (key == 1)
    {
        currentFigure->move(-1, 0);
        if(boundariesIsBroken())
            currentFigure->move(1, 0);
    }
    if (key == 2)
    {
        currentFigure->move(1, 0);
        if(boundariesIsBroken())
            currentFigure->move(-1, 0);
    }
    if (key == 3)
    {
        currentFigure->rotateTetromino(true);
        if(boundariesIsBroken())
            currentFigure->rotateTetromino(false);
    }
    if (key == 4)
    {
        currentFigure->move(0, 1);
        if(boundariesIsBroken())
            currentFigure->move(0, -1);
    }
    if (key == 5)
    {
        currentFigure->move(0, distanceToLocked());

    }
    key = 0;
}

void Game::fallingFigure(sf::Clock& timer, float pause)
{
    if (timer.getElapsedTime().asSeconds() >= pause) {
        timer.restart();
        currentFigure->move(0,1);
        if(boundariesIsBroken())
        {
            currentFigure->move(0, -1);
            isLocked();
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

int Game::distanceToLocked()
{
    int minDistance = 25;

    for (Block item: currentFigure->getStatus())
    {
        int i = 0;
        while (field.getGameBoard(item.y + currentFigure->get_offset_y() + i, item.x + currentFigure->get_offset_x()) == 0 && i < HEIGHT - 2)
        {
            ++i;
        }
        if ((i-1) < minDistance)
            minDistance = i - 1;

    }


    return minDistance;
}

void Game::showMenu(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("Font.ttf");
    sf::Text text("", font, 20);
    text.setColor(sf::Color::White);
    text.setString("Start");
    text.setPosition(0, 0);
    window.draw(text);
}
void Game::drawNextFigureBlock(sf::RenderWindow &window)
{
    int offsetX = 0, offsetY = 0;
    oneBlock.sprite.setTextureRect(sf::IntRect((nextFigure->getColor()-1) * CELL_SIZE,0,CELL_SIZE , CELL_SIZE) );
    for (Block& item: nextFigure->getStatus())
    {
        if (nextFigure->getType() == 6)
            offsetX = -25;
        else if (nextFigure->getType() == 7)
            offsetX = 8;
        oneBlock.sprite.setPosition(static_cast<float>(item.x*CELL_SIZE +1122 + offsetX), static_cast<float>(item.y*CELL_SIZE + 275 + offsetY));
        window.draw(oneBlock.sprite);
    }
}
