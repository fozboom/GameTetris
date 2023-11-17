#include "Game.h"


Game::Game():
buttonRowsCount("ROWS", 150, 250, "images/rows.png",160, 485, "fonts/D.ttf", 48, 240, 530),
buttonPause("PAUSE", 120, 120, "images/pause.png", 1108, 615, "fonts/D.ttf", 24, 0,0),
buttonGameOver("GameOver", 1448, 916, "images/gameOver.png", 0, 0, "fonts/D.ttf", 24, 0,0),
oneBlock("images/color_cubes.png", 0, 0),
pauseBoard("images/shadowBoard.png",0,0),
field(),
lines_in_a_row(0), score(0), time(10), countLines(0)
{
    getAllFigures();
    readFileBestPlayers("BestPlayersInfo.txt");
    currentFigure = getRandomFigure();
    nextFigure = getRandomFigure();
    currentFigure->setDistanceToCollision(distanceToLocked());
    font.loadFromFile("fonts/D.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
}

void Game::draw(sf::RenderWindow& window)
{
    drawGrid(window);
    buttonRowsCount.draw(window);
    buttonPause.draw(window);
    buttonRowsCount.drawNumber(window, countLines);
    currentFigure->setDistanceToCollision(distanceToLocked());
    currentFigure->drawFigure(window);
    drawNextFigureBlock(window);
    getAllFigures();
    showGameTime(window);
    showScore(window);
    showBestPlayersBlock(window);
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

void Game::drawBoardImage (sf::RenderWindow& window)
{

    field.drawGameBoard(window);
}

void Game::drawGrid(sf::RenderWindow& window)
{
    std::vector<Block> tmp = currentFigure->newCondition();



    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (field.getGameBoard(i,j) != 0)
            {
                oneBlock.sprite.setTextureRect(sf::IntRect((field.getGameBoard(i, j) - 1) * CELL_SIZE, 0, CELL_SIZE , CELL_SIZE) );
                oneBlock.sprite.setPosition(static_cast<float>(j*CELL_SIZE+576), static_cast<float>(i*CELL_SIZE+175));
                window.draw(oneBlock.sprite);
            }
        }
    }
}

void Game::buttonAction(int& key)
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
        currentFigure->rotateTetromino(false);
        if(boundariesIsBroken())
            currentFigure->rotateTetromino(true);
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
            lineFilled();
        }
    }
}

bool Game::gameOver(sf::RenderWindow& window, sf::Event& event)
{
    std::vector<Block> object = currentFigure->newCondition();
    for (Block& item: object)
    {
        if (boundariesIsBroken() && (item.y == 0))
        {

            Text nickName(24, true, "fonts/D.ttf");
            while(window.waitEvent(event))
            {
                if (event.type == sf::Event::TextEntered)
                {
                    nickName.typeOn(event, window);
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        break;
                    }
                }
                window.clear();
                buttonGameOver.draw(window);
                nickName.draw(window);
                window.display();
            }
            return true;
        }
    }
    return false;
}

void Game::lineFilled()
{
    lines_in_a_row = 0;
    bool isFull = true;
    for (int i = HEIGHT - 1; i >= 0; --i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (field.getGameBoard(i, j) == 0)
            {
                isFull =  false;
                break;
            }
        }
        if (isFull)
        {
            lines_in_a_row++;
        }
        if (!isFull && lines_in_a_row>0)
        {
            countLines += lines_in_a_row;
            std::cout << lines_in_a_row << std::endl;
            deleteLine(i, lines_in_a_row);
            i+= lines_in_a_row;
            scoreBooster(lines_in_a_row);
            std::cout << lines_in_a_row << std::endl;
        }
        isFull = true;
    }
}

void Game::deleteLine(int num, int count)
{
    for(int k = count; k > 0; --k)
    {
        for (int i = num + count; i > 0; --i)
        {
            for (int j = 0; j < WIDTH; ++j)
            {
                field.setGameBoard(i, j, field.getGameBoard(i - 1, j));
            }
        }
        for (int j = 0; j < WIDTH; ++j)
            field.setGameBoard(0, j, 0);
    }
}

int Game::distanceToLocked()
{
    int minDistance = 20;

    for (Block& item: currentFigure->getStatus())
    {
        int i = 0;
        while (field.getGameBoard(item.y + currentFigure->get_offset_y() + i, item.x + currentFigure->get_offset_x()) == 0 && i < HEIGHT - 1)
        {
            ++i;
        }
        if ((i-1) < minDistance)
            minDistance = i-1;

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
        if (!(read >> i.nickName >> i.score))
        {
            throw ExceptionFile("Ошибка чтения данных из файла");
        }
    }
}

void Game::writeFileBestPlayers(const char* fileName)
{
    checkStatisticBeforeSave();
    std::ofstream input;
    input.open(fileName);
    if (!input.is_open()) {throw ExceptionFile("Ошибка открытия файла для записи");}

    for (int i = 0; i < COUNT_PEOPLE; ++i)
    {
        input << infoBlock[i].nickName << " " << infoBlock[i].score << "\n";
    }
}

void Game::showBestPlayersBlock(sf::RenderWindow& window)
{
    int offset_x = 70, offset_y = 0;
    for (int i = 0; i < COUNT_PEOPLE; ++i)
    {
        text.setString(infoBlock[i].nickName);
        text.setPosition(static_cast<float>(175), static_cast<float>(195 + offset_y));
        window.draw(text);
        number = std::to_string(infoBlock[i].score);
        text.setString(number);
        text.setPosition(static_cast<float>(175 + offset_x), static_cast<float>(195 + offset_y));
        window.draw(text);
        offset_y += 30;
    }

}

void Game::scoreBooster(int& _lines_in_a_row)
{
    if (_lines_in_a_row == 1)
    {
        score += 40 + static_cast<int>( 0.05 * time * 40);
        std::cout << "+80\n";
    }
    else if(_lines_in_a_row == 2)
    {
        score += 100 + static_cast<int>( 0.05 * time * 100);
        std::cout << "+200\n";
    }
    else if(_lines_in_a_row == 3)
    {
        score += 300 + static_cast<int>( 0.05 * time * 300);
        std::cout << "+600\n";
    }
    else if(_lines_in_a_row == 4)
    {
        score += 1200 + static_cast<int>( 0.05 * time * 1200);
        std::cout << "+2400\n";
    }
    lines_in_a_row = 0;

}

void Game::showScore(sf::RenderWindow& window)
{
    float x = 1295, y = 96;
    number = std::to_string(score);
    text.setString(number);
    if (score < 10)
        x -= 0;
    else if (score < 100)
        x -= 5;
    else if (score < 1000)
        x -= 10;
    else if (score < 10'000)
        x -= 15;
    else if (score < 100'000)
        x -= 20;
    else if (score < 1'000'000)
        x -= 25;
    else if (score < 10'000'000)
        x -= 30;
    text.setPosition(x, y);
    window.draw(text);
}

void Game::showGameTime(sf::RenderWindow &window)
{
    time = gameTime.getElapsedTime().asSeconds();

    if(time < 10)
    {
        number = std::to_string(time);
        text.setString("00:0" + number);
    }
    else if (time < 60)
    {
        number = std::to_string(time);
        text.setString("00:" + number);
    }
    else if (time < 600)
    {
        std::string seconds;

        number = std::to_string(time/60);
        seconds = std::to_string(time%60);
        if (time%60 < 10)
            text.setString("0"+number + ":0" + seconds);
        else
            text.setString("0"+number + ":" + seconds);
    }
    else
    {
        std::string seconds;
        number = std::to_string(time/60);
        seconds = std::to_string(time%60);
        if (time%60 < 10)
            text.setString(number + ":0" + seconds);
        else
            text.setString(number + ":" + seconds);
    }
    text.setPosition(1293,45);
    window.draw(text);

}

void Game::checkStatisticBeforeSave()
{
    for (int i = 0; i < COUNT_PEOPLE; ++i)
    {
        if (score > infoBlock[i].score)
        {
            for (int k = COUNT_PEOPLE-1; k > i; --k)
            {
                infoBlock[k].score = infoBlock[k-1].score;
            }
            infoBlock[i].score = this->score;
            break;
        }

    }
}



int Game::keyPressCheck(sf::Event& event, sf::RenderWindow& window, int & key, Text& m)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
        {
            key = 1;
            return 3;
        }
        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
        {
            key = 2;
            return 3;
        }
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
        {
            key = 3;
            return 3;
        }
        if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
        {
            key = 4;
            return 3;
        }
        if (event.key.code == sf::Keyboard::Space)
        {
            key = 5;
            return 3;
        }
        if (event.key.code == sf::Keyboard::RAlt)
        {
            writeFileBestPlayers("BestPlayersInfo.txt");
            window.close();
            return 3;
        }
        if (event.key.code == sf::Keyboard::LControl)
        {
            writeFileBestPlayers("BestPlayersInfo.txt");
            return 1;
        }

        if (event.key.code == sf::Keyboard::RAlt)
        {
            writeFileBestPlayers("BestPlayersInfo.txt");
            return 0;
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            buttonPause.updateSprite("images/unpause.png");

            while (window.waitEvent(event))
            {
                window.clear();
                window.draw(pauseBoard.sprite);
                draw(window);
                window.display();
                if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)||
                   (sf::IntRect(1104, 619, 120, 120).contains(sf::Mouse::getPosition(window))
                    && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    buttonPause.updateSprite("images/pause.png");
                    break;
                }
            }

        }

    }
    return mousePressedCheck(event, window);

}


bool Game::drawWindow(sf::RenderWindow &window, GameMenu& menu)
{
    sf::Clock timer;
    float pause = 0.27f;
    int key = 0;
    int toDo;
    Text m(24, true, "fonts/D.ttf");
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if(gameOver(window, event))
            {

            }
            if(menu.getIsMenu())
                menu.keyPressCheck(event);
            else
            {
                toDo = keyPressCheck(event, window, key, m);
                if (toDo == 1) return true;
                else if (toDo == 0) return false;

            }

        }

        window.clear();

        if(menu.getIsMenu())
            menu.showMenu(window);
        else
        {
            fallingFigure(timer, pause);
            buttonAction(key);

            if(gameOver(window, event))
            {
                //std::cout << "Finish";
                //exit(EXIT_SUCCESS);
            }
            drawBoardImage(window);
            draw(window);

            m.draw(window);
        }
        window.display();

    }


}


int Game::mousePressedCheck(sf::Event& event, sf::RenderWindow& window)
{
    if (sf::IntRect(1109, 483, 110, 110).contains(sf::Mouse::getPosition(window))
        && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return 1;
    }
    if ((sf::IntRect(buttonPause.getPositionX(), buttonPause.getPositionY(),
                     buttonPause.getWidth(), buttonPause.getHeight()).contains(sf::Mouse::getPosition(window))
                      && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        buttonPause.updateSprite("images/unpause.png");
        window.clear();
        window.draw(pauseBoard.sprite);
        draw(window);
        window.display();
        while (window.waitEvent(event))
        {
            if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)||
               (sf::IntRect(1104, 619, 120, 120).contains(sf::Mouse::getPosition(window))
                && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
            {
                buttonPause.updateSprite("images/pause.png");
                break;
            }
        }
    }
    return 3;
}


