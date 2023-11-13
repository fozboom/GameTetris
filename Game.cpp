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

Game::Game():oneBlock("color_cubes.png"), field()
{
    getAllFigures();
    readFileBestPlayers("BestPlayersInfo.txt");
    currentFigure = getRandomFigure();
    nextFigure = getRandomFigure();
    currentFigure->setDistanceToCollision(distanceToLocked());
    font.loadFromFile("AbhayaLibre-Bold.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setColor(sf::Color::Black);
}

Figure*& Game::getRandomFigure()
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
    getAllFigures();
}

void  Game::getAllFigures()
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
    for (Block& item: object)
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
                oneBlock.sprite.setPosition(static_cast<float>(j*CELL_SIZE+516), static_cast<float>(i*CELL_SIZE+158));
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
    for (Block& item: object)
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

    for (Block& item: currentFigure->getStatus())
    {
        int i = 0;
        while (field.getGameBoard(item.y + currentFigure->get_offset_y() + i, item.x + currentFigure->get_offset_x()) == 0 && i < HEIGHT - 1)
        {
            ++i;
        }
        if ((i-1) < minDistance)
            minDistance = i - 1;

    }


    return minDistance;
}


void Game::drawNextFigureBlock(sf::RenderWindow &window)
{
    int offsetX, offsetY;
    oneBlock.sprite.setTextureRect(sf::IntRect((nextFigure->getColor()-1) * CELL_SIZE,0,CELL_SIZE , CELL_SIZE) );
    for (Block& item: nextFigure->getStatus())
    {
        offsetX = 0, offsetY = 0;
        if (nextFigure->getType() == 6)
            offsetX = -21;
        else if (nextFigure->getType() == 7)
            offsetX = 8;
        oneBlock.sprite.setPosition(static_cast<float>(item.x*CELL_SIZE +1122 + offsetX), static_cast<float>(item.y*CELL_SIZE + 261 + offsetY));
        window.draw(oneBlock.sprite);
    }
}

void Game::readFileBestPlayers(const char* fileName)
{
    std::ifstream read;
    read.open(fileName);
    if (!read.is_open()) {throw ExceptionFile("Ошибка открытия файла для чтения");}

    for (auto & i : infoBlock)
    {
        if (!(read >> i.nickName >> i.scope))
        {
            throw ExceptionFile("Ошибка чтения данных из файла");
        }
    }
}

void Game::writeFileBestPlayers(const char* fileName)
{
    std::ofstream input;
    input.open(fileName);
    if (!input.is_open()) {throw ExceptionFile("Ошибка открытия файла для записи");}

    for (int i = 0; i < COUNT_PERSONS; ++i)
    {
        rewind(stdin);
        std::cin.getline(infoBlock[i].nickName, 10);
        rewind(stdin);
        std::cin >> infoBlock[i].scope;
        input << infoBlock[i].nickName << " " << infoBlock[i].scope << "\n";
    }
}

void Game::showBestPlayersBlock(sf::RenderWindow& window)
{
    int offset_x = 70, offset_y = 0;
    std::string x;
    for (int i = 0; i < COUNT_PERSONS; ++i)
    {
        text.setString(infoBlock[i].nickName);
        text.setPosition(160, 230 + offset_y);
        window.draw(text);
        x = std::to_string(infoBlock[i].scope);
        text.setString(x);
        text.setPosition(160 + offset_x, 230 + offset_y);
        window.draw(text);
        offset_y += 30;
    }

}