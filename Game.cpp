#include "Game.h"


Game::Game(): // Конструктор по умолчанию класса Game инициализирует следующие члены
        buttonRowsCount("./images/rows.png",160, 485), // Инициализация кнопки, отображающей количество строк
        buttonRestart("RESTART",111,112, "./images/restart.png",1110,478), // Инициализация кнопки перезапуска игры
        buttonPause("PAUSE", 120, 120, "./images/pause.png", 1108, 615), // Инициализация кнопки паузы
        buttonGameOver("./images/gameOver.png", 0, 0), // Инициализация кнопки Game Over
        buttonMusic("Music",62,34, "./images/buttonON.png", 220,684), // Инициализация кнопки для управления музыкой
        oneBlock("./images/color_cubes.png", 0, 0), // Инициализация блока для игры
        pauseBoard("./images/shadowBoard.png",0,0), // Инициализация доски для паузы
        lines_in_a_row(0), score(0), time(10), countLines(0), fileTime(0), tmpTime(0) // Инициализация переменных игры
{
    music.openFromFile("./music/music.ogg");
    music.setVolume(30);
    music.play();
    getStartBoxOfFigure();
    readFileBestPlayers("./BestPlayersInfo.txt");
    currentFigure = getRandomFigure();
    nextFigure = getRandomFigure();
    currentFigure->setDistanceToCollision(distanceToLocked());
    font.loadFromFile("./fonts/D.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    // В теле конструктора мы загружаем и проигрываем музыку, получаем начальную фигуру и блок,
    // загружаем шрифт и устанавливаем его для текста, а также загружаем информацию о лучших игроках.
}

void Game::draw(sf::RenderWindow& window)  // В этом методе мы отрисовываем все элементы игры
{
    drawPlacedBlocks(window); // Отрисовка блоков на игровом поле
    buttonRowsCount.draw(window); // Отрисовка кнопки количества строк
    buttonPause.draw(window); // Отрисовка кнопки "пауза"
    buttonRestart.draw(window); // Отрисовка кнопки "перезапуск"
    buttonRowsCount.drawNumber(window, countLines); // Отображение числа строк
    buttonMusic.draw(window); // Отрисовка кнопки "музыка"
    currentFigure->setDistanceToCollision(distanceToLocked()); // Установка расстояния текущей фигуры до коллизии
    currentFigure->drawFigure(window); // Отрисовка текущей фигуры
    drawNextFigureBlock(window); // Отрисовка следующей фигуры
    getAllFigures(); // Получение всех фигур
    showGameTime(window); // Отображение времени игры
    showScore(window); // Отображение счета
    showBestPlayersBlock(window); // Отображение блока лучших игроков
}

// Функция получения случайной фигуры для игры
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

    // Генерируем случайный индекс из диапазона от 0 до размера вектора фигур
    int randomIndex = generateRandomNumber(0, static_cast<int>(figures.size()) - 1);
    Figure* fig = figures[randomIndex]; // Выбираем случайную фигуру

    // Удаляем выбранную фигуру из вектора
    figures.erase(figures.begin() + randomIndex);

    return fig; // Возвращаем фигуру
}

void Game::getStartBoxOfFigure()
{
    figures.push_back(new J_Block());
    figures.push_back(new T_Block());
    figures.push_back(new L_Block());
    figures.push_back(new I_Block());
    figures.push_back(new O_Block());
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

// Функция для проверки, нарушает ли текущая фигура границы игрового поля.
bool Game::boundariesIsBroken()
{
    std::vector<Block> object = currentFigure->calculateMovedPosition( );
    for (auto & i : object)
    {
        if (i.x< 0 || i.x > field.getWidth() - 1 || field.getGameBoard(i.y, i.x) != 0 || i.y > field.getHeight()- 1)
            return true;
    }
    return false;
}

void Game::isLocked() // Функция для проверки, зафиксирована ли фигура на игровом поле.
{
    std::vector<Block> object = currentFigure->calculateMovedPosition(); // Расчет положения блока
    for (Block& item: object)
    {
        field.setGameBoard(item.y, item.x, currentFigure->getColor()); // Установка цвета блока на игровое поле
    }
    currentFigure = nextFigure; // Текущей фигурой становится следующая
    nextFigure = getRandomFigure(); // Генерируем новую случайную фигуру.
}

void Game::drawBoardImage (sf::RenderWindow& window) // Функция для отрисовки изображения доски
{
    field.drawGameBoard(window); // Отрисовка игрового поля
}

void Game::drawPlacedBlocks(sf::RenderWindow& window) // Функция для отрисовки размещенных блоков
{
    std::vector<Block> tmp = currentFigure->calculateMovedPosition();

    for (int i = 0; i < field.getHeight(); ++i)
    {
        for (int j = 0; j < field.getWidth(); ++j)
        {
            if (field.getGameBoard(i,j) != 0)
            {
                oneBlock.sprite.setTextureRect(sf::IntRect((field.getGameBoard(i, j) - 1) * CELL_SIZE, 0, CELL_SIZE , CELL_SIZE));
                oneBlock.sprite.setPosition(static_cast<float>(j*CELL_SIZE+576), static_cast<float>(i*CELL_SIZE+175));
                window.draw(oneBlock.sprite); // Отрисовка блока в окне
            }
        }
    }
}

void Game::buttonAction(int& key)
{
    if (key == 1)   //влево
    {
        currentFigure->move(-1, 0);
        if(boundariesIsBroken())
            currentFigure->move(1, 0);
    }
    if (key == 2)   //вправо
    {
        currentFigure->move(1, 0);
        if(boundariesIsBroken())
            currentFigure->move(-1, 0);
    }
    if (key == 3)   //вверх
    {
        currentFigure->rotateFigure(false);
        if(boundariesIsBroken())
            currentFigure->rotateFigure(true);
    }
    if (key == 4)   //вниз
    {
        currentFigure->move(0, 1);
        if(boundariesIsBroken())
            currentFigure->move(0, -1);
    }
    if (key == 5)   //пробел
    {
        currentFigure->move(0, distanceToLocked());

    }
    key = 0;
}

void Game::fallingFigure(sf::Clock& timer, float pause) // Метод для обработки падения фигур
{
    if (timer.getElapsedTime().asSeconds() >= pause) // Если прошедшее время больше или равно паузе
    {
        timer.restart(); // Перезапускаем таймер
        currentFigure->move(0,1); // Смещаем текущую фигуру вниз
        if(boundariesIsBroken()) // Если границы нарушены
        {
            currentFigure->move(0, -1); // Возвращаем фигуру обратно
            isLocked(); // Зафиксируем фигуру на игровом поле
            checkAndClearFilledLines(); // Проверяем и очищаем заполненные линии
        }
    }
}

bool Game::gameOver(sf::RenderWindow& window, sf::Event& event)
{
    // Создаем вектор блоков, используя текущую фигуру и вычисляя ее смещенное положение
    std::vector<Block> object = currentFigure->calculateMovedPosition( );

    // Для каждого блока в векторе
    for (Block& item: object)
    {
        // Проверяем, нарушены ли границы и находится ли блок на верхней границе поля
        if (boundariesIsBroken() && (item.y == 0))
        {
            // Создаем текстовое поле для ввода имени пользователя
            Text nick(30, true, "./fonts/D.ttf");

            // Очистка окна
            window.clear();

            // Отрисовка кнопки завершения игры
            buttonGameOver.draw(window);

            // Отрисовка текстового поля
            nick.draw(window);

            // Обновление окна
            window.display();

            // Ожидание события в окне
            while(window.waitEvent(event))
            {
                // Если событие - это ввод текста
                if (event.type == sf::Event::TextEntered)
                {
                    // Вводим текст в текстовое поле
                    nick.typeOn(event, window);
                }

                // Если событие - это нажатие клавиши
                if (event.type == sf::Event::KeyPressed)
                {
                    // Если нажата клавиша Enter
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        // Запоминаем введенное имя пользователя
                        nickName = nick.getString();
                        break;
                    }
                }

                // Очистка окна
                window.clear();

                // Отрисовка кнопки завершения игры
                buttonGameOver.draw(window);

                // Отрисовка текстового поля
                nick.draw(window);

                // Обновление окна
                window.display();
            }

            // Инициализация вектора поля
            field.initializeVector();

            // Сохранение текущего состояния игры в файл
            saveGameToFile("Game");

            // Возвращаем, что игра окончена
            return true;
        }
    }

    // Возвращаем, что игра не закончилась
    return false;
}

// Функция проверки и удаления заполненных линий
void Game::checkAndClearFilledLines()
{
    // Флаг, чтобы проверить, полностью ли заполнена строка
    bool isFull = true;

    // Переменная, чтобы отслеживать количество заполненных строк подряд
    lines_in_a_row = 0;

    // Обходим каждую строку снизу вверх
    for (int i = field.getHeight() - 1; i >= 0; --i)
    {
        // Обходим каждый элемент в строке слева направо
        for (int j = 0; j < field.getWidth(); ++j)
        {
            // Если элемент свободен (равен 0), значит строка не полностью заполнена
            if (field.getGameBoard(i, j) == 0)
            {
                isFull =  false;
                break;
            }
        }

        // Если строка полностью заполнена увеличиваем счетчик заполненных строк подряд
        if (isFull)
        {
            lines_in_a_row++;
        }

        // Если встретилась незаполненная строка, и до этого были заполненные строки
        if (!isFull && lines_in_a_row > 0)
        {
            // Увеличиваем общий счетчик удаленных строк на количество заполненных строк подряд
            countLines += lines_in_a_row;
            // Удаляем заполненные строки начиная с текущей позиции
            deleteLine(i, lines_in_a_row);
            // Сдвигаем индекс строки вниз на количество удаленных строк (так как они были удалены)
            i += lines_in_a_row;
            // Увеличиваем очки пользователя в зависимости от количества одновременно удаленных строк
            scoreBooster(lines_in_a_row);
        }

        // Сбрасываем флаг к следующей проверке строки
        isFull = true;
    }
}



// Функция для удаления определенной строки
void Game::deleteLine(int num, int count)
{
    // Повторяем столько раз, сколько строк нужно удалить
    for (int k = count; k > 0; --k)
    {
        // Для каждой строки от указанной до верхней границы поля
        for (int i = num + count; i > 0; --i)
        {
            // Для каждого блока в строке
            for (int j = 0; j < field.getWidth(); ++j)
            {
                // Устанавливаем значение блока в текущей строке равным значению блока в строке выше
                // Таким образом, "удаляя" строку, мы сдвигаем все строки выше на одну вниз
                field.setGameBoard(i, j, field.getGameBoard(i - 1, j));
            }
        }
    }
}

// Функция для получения расстояния до заблокированных ячеек
int Game::distanceToLocked()
{
    // Изначально задаем максимально большое расстояние
    int minDistance = 20;

    // Обходим каждый блок в текущей фигуре
    for (Block& item: currentFigure->getStatus())
    {
        // Счетчик для измерения расстояния
        int i = 0;

        // Пока не достигнем заблокированной ячейки или края игрового поля
        while ((field.getGameBoard(item.y + currentFigure->get_offset_y() + i, item.x + currentFigure->get_offset_x()) == 0) && i < field.getHeight() - 1)
        {
            // Увеличиваем счетчик
            ++i;
        }

        // Если текущее расстояние меньше минимального, то обновляем минимальное расстояние
        if ((i-1) < minDistance)
            minDistance = i-1;
    }

    // Возвращаем минимальное расстояние до заблокированной ячейки
    return minDistance;
}


// Функция для отрисовки следующей фигуры на экране
void Game::drawNextFigureBlock(sf::RenderWindow &window)
{
    int offsetX, offsetY; // переменные для коррекции позиции фигуры на экране

    // Устанавливаем текстуру и размеры для блока следующей фигуры
    oneBlock.sprite.setTextureRect(sf::IntRect((nextFigure->getColor()-1) * CELL_SIZE,0,CELL_SIZE , CELL_SIZE));

    // Проходим по всем блокам следующей фигуры
    for (Block& item: nextFigure->getStatus())
    {
        offsetX = 0, offsetY = 0; // обнуляем смещение для каждого нового блока

        // Делаем корректировку смещения в зависимости от типа следующей фигуры
        if (nextFigure->getType() == 6)
            offsetX = -21;  // для фигуры типа 6
        else if (nextFigure->getType() == 7)
            offsetX = 8;   // для фигуры типа 7

        // Устанавливаем позицию блока на экране
        oneBlock.sprite.setPosition(static_cast<float>(item.x*CELL_SIZE +1122 + offsetX), static_cast<float>(item.y*CELL_SIZE + 261 + offsetY));

        // Рисуем блок на экране
        window.draw(oneBlock.sprite);
    }
}

// Функция для чтения файла с информацией о лучших игроках
void Game::readFileBestPlayers(const char* fileName)
{
    // Открываем файл на чтение
    std::ifstream read(fileName);

    // Если файл не удалось открыть, бросаем исключение
    if (!read.is_open()) { throw ExceptionFile("Ошибка открытия файла для чтения"); }

    std::string tempName;  // Временная переменная для хранения имени игрока
    int tempScore;         // Временная переменная для хранения очков игрока

    // Читаем из файла пока есть что читать
    while (read >> tempName >> tempScore)
    {
        // Создаем временный объект с информацией об игроке
        PlayerInfo tempPlayerInfo(tempName, tempScore);

        // Помещаем информацию об игроке в очередь
        infoQueue.enqueue(tempPlayerInfo);
    }

    // Если конец файла не достигнут, бросаем исключение
    if (!read.eof())
    {
        throw ExceptionFile("Ошибка чтения данных из файла");
    }
}

// Функция для записи файла с информацией о лучших игроках
void Game::writeFileBestPlayers(const char* fileName)
{
    // Проверяем статистику перед сохранением
    checkStatisticBeforeSave();

    std::ofstream input;
    // Открываем файл на запись
    input.open(fileName);

    // Если файл не удалось открыть, бросаем исключение
    if (!input.is_open()) {throw ExceptionFile("Ошибка открытия файла для записи");}

    // Пока очередь не пуста
    while (!infoQueue.isEmpty()){
        // Извлекаем информацию об игроке из очереди
        PlayerInfo tempPlayerInfo = infoQueue.front();

        // Записываем имя игрока и очки в файл
        input << tempPlayerInfo.getNickName() << " " << tempPlayerInfo.getScore() << "\n";

        // Удаляем иформацию об игроке из очереди
        infoQueue.dequeue();
    }
}

// Функция для отображения блока с лучшими игроками
void Game::showBestPlayersBlock(sf::RenderWindow& window)
{
    int offset_x = 90, offset_y = 0;  // Задаем начальные отступы
    Queue<PlayerInfo> tempQueue = infoQueue;  // Создаем временную очередь, копируя имеющуюся

    // Отображаем информацию о первых пяти игроках из очереди
    for (int i = 0; i < 5; ++i)
    {
        // Извлекаем информацию об игроке из очереди
        PlayerInfo tempPlayerInfo = tempQueue.front();

        // Задаем текстовую строку и позицию для имени игрока
        text.setString(tempPlayerInfo.getNickName());
        text.setPosition(static_cast<float>(165), static_cast<float>(195 + offset_y));

        // Отрисовываем текст
        window.draw(text);

        // Приводим очки игрока к строковому виду и задаем текстовую строку и позицию для очков
        number = std::to_string(tempPlayerInfo.getScore());
        text.setString(number);
        text.setPosition(static_cast<float>(175 + offset_x), static_cast<float>(195 + offset_y));

        // Отрисовываем текст
        window.draw(text);

        // Удаляем информацию об игроке из очереди
        tempQueue.dequeue();

        // Увеличиваем вертикальный отступ для следующего игрока
        offset_y += 30;
    }

    // Очищаем оставшуюся очередь
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue();
    }
}

// Функция для увеличения очков игрока в зависимости от количества очищенных строк подряд
void Game::scoreBooster(int& _lines_in_a_row)
{
    // Если очищена одна строка
    if (_lines_in_a_row == 1)
    {
        // Увеличиваем счет на 40 + 5% от времени, умноженного на 40
        score += 40 + static_cast<int>( 0.05 * time * 40);
        // Выводим информацию
        std::cout << "+80\n";
    }
        // Если очищено две строки
    else if(_lines_in_a_row == 2)
    {
        // Увеличиваем счет на 100 + 5% от времени, умноженного на 100
        score += 100 + static_cast<int>( 0.05 * time * 100);
        // Выводим информацию
        std::cout << "+200\n";
    }
        // Если очищено три строки
    else if(_lines_in_a_row == 3)
    {
        // Увеличиваем счет на 300 + 5% от времени, умноженного на 300
        score += 300 + static_cast<int>( 0.05 * time * 300);
        // Выводим информацию
        std::cout << "+600\n";
    }
        // Если очищено четыре строки
    else if(_lines_in_a_row == 4)
    {
        // Увеличиваем счет на 1200 + 5% от времени, умноженного на 1200
        score += 1200 + static_cast<int>( 0.05 * time * 1200);
        // Выводим информацию
        std::cout << "+2400\n";
    }
    // Обнуляем счетчик очищенных строк подряд
    lines_in_a_row = 0;
}

// Функция для отображения количество очков игрока на экране
void Game::showScore(sf::RenderWindow& window)
{
    float x = 1295, y = 96;  // Задаем координаты для отображения

    number = std::to_string(score);  // Преобразуем счет в строку
    text.setString(number);  // Устанавливаем эту строку на текстовое поле

    // В зависимости от счета, корректируем координату X для правильного центрирования
    if (score < 10)
        x -= 0;   // Если счет меньше 10, то не корректируем
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

    // Устанавливаем позицию текстового поля
    text.setPosition(x, y);

    // Обрисовываем текстовое поле в окне
    window.draw(text);
}

void Game::showGameTime(sf::RenderWindow &window)
{
    time = fileTime + tmpTime + gameTime.getElapsedTime().asSeconds();

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

// Метод для проверки статистики перед сохранением
void Game::checkStatisticBeforeSave()
{
    // Создаем временную очередь для игрока
    Queue<PlayerInfo> tempQueue;
    // Инициализируем флаг добавления счета как ложный
    bool isScoreAdded = false;

    //Пока очередь информации о игроке не пуста
    while(!infoQueue.isEmpty())
    {
        // Переменная текущего элемента из очереди игроков
        PlayerInfo current = infoQueue.front();
        // Удаляем текущий элемент из очереди информации
        infoQueue.dequeue();

        // Если счет ещё не добавлен и текущий счет больше счета текущего элемента
        if (!isScoreAdded && score > current.getScore())
        {
            // Создаем новую информацию о счете игрока
            PlayerInfo newScore{nickName, score};
            // Добавляем новый счет в временную очередь
            tempQueue.enqueue(newScore);
            // Помечаем, что счет добавлен
            isScoreAdded = true;
        }

        // Добавляем текущий элемент во временную очередь
        tempQueue.enqueue(current);
    }

    // Если новый счет еще не добавлен
    if (!isScoreAdded)
    {
        // Создаем новую информацию о счете
        PlayerInfo newScore{nickName, score};
        // Добавляем новый счет во временную очередь
        tempQueue.enqueue(newScore);
    }

    // Перемещаем все элементы обратно в очередь информации о игроке
    while(!tempQueue.isEmpty())
    {
        // Добавляем в начало очереди информации первый элемент временной очереди
        infoQueue.enqueue(tempQueue.front());
        // Удаляем первый элемент временной очереди
        tempQueue.dequeue();
    }
}



int Game::keyPressCheck(sf::Event& event, sf::RenderWindow& window, int & key, GameMenu& menu)
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
            saveGameToFile("Game");
            menu.setIsMenu(true);
            return 1;
        }
        if (event.key.code == sf::Keyboard::LControl)
        {
            return 1;
        }


        if (event.key.code == sf::Keyboard::Escape)
        {
            int tmp= time - fileTime;
            buttonPause.updateSprite("./images/unpause.png");
            buttonPause.playMusic();
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
                    buttonPause.updateSprite("./images/pause.png");
                    break;
                }
            }
            gameTime.restart();
            tmpTime = tmp;
        }

    }
    return mousePressedCheck(event, window);

}


// Метод обработки цикла игры
bool Game::processGameCycle(sf::RenderWindow &window, GameMenu& menu)
{
    // Создаем таймер
    sf::Clock timer;
    // Устанавливаем начальное время паузы
    float pause = 0.27f;
    // Инициализируем клавишу
    int key = 0;
    // Инициализируем переменную для операции, которую нужно выполнить
    int toDo;
    // Пока окно открыто
    while (window.isOpen())
    {
        // Инициализируем событие
        sf::Event event{};
        // Пока есть события в очереди
        while (window.pollEvent(event))
        {
            // Если мы в меню
            if(menu.getIsMenu())
                // Проверяем нажатие клавиш
                menu.keyPressCheck(event);
                // Иначе
            else
            {
                // Проверяем нажатие клавиш и возвращаем действие, которое надо выполнить
                toDo = keyPressCheck(event, window, key, menu);
                // Если нам надо выйти
                if (toDo == 1) return true;
            }

        }

        // Очищаем окно
        window.clear();

        // Если мы в меню
        if(menu.getIsMenu())
            // Отображаем меню
            menu.showMenu(window, *this);
            // Иначе
        else
        {
            // Падение фигуры
            fallingFigure(timer, pause);
            // Действие кнопки
            buttonAction(key);

            // Если игра окончена
            if(gameOver(window, event))
            {
                // Возвращаемся в меню
                menu.setIsMenu(true);
                // Записываем лучших игроков
                writeFileBestPlayers("./BestPlayersInfo.txt");
                // Возвращаем истину
                return true;
            }
            // Рисуем изображение доски
            drawBoardImage(window);
            // Рисуем игровое поле
            draw(window);

        }
        // Отображаем окно
        window.display();

    }
}


int Game::mousePressedCheck(sf::Event& event, sf::RenderWindow& window)
{
    if (sf::IntRect(1110, 478, 111, 112).contains(sf::Mouse::getPosition(window))
        && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        buttonRestart.playMusic();
        return 1;
    }
    if ((sf::IntRect(buttonPause.getPositionX(), buttonPause.getPositionY(),
                     buttonPause.getWidth(), buttonPause.getHeight()).contains(sf::Mouse::getPosition(window))
                      && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        buttonPause.updateSprite("images/unpause.png");
        buttonPause.playMusic();
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

    if (sf::IntRect(220, 684, 62, 34).contains(sf::Mouse::getPosition(window))
        && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(!buttonMusic.getIsPressed())
        {
            buttonMusic.playMusic();
            music.pause();
            buttonMusic.updateSprite("images/buttonOFF.png");
            buttonMusic.setIsPressed(true);
        }
        else
        {
            buttonMusic.playMusic();
            music.play();
            buttonMusic.updateSprite("images/buttonON.png");
            buttonMusic.setIsPressed(false);
        }
    }
    return 3;
}

// Метод для сохранения текущей игры в файл
void Game::saveGameToFile(std::string fileName)
{
    // Открываем файл в бинарном режиме
    std::ofstream outFile(fileName, std::ios::binary);

    // Если файл не открывается, выводим сообщение об ошибке и выходим из функции
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для сохранения игры" << std::endl;
        return;
    }

    // Записываем в файл значение переменной score
    outFile.write(reinterpret_cast<const char*>(&score), sizeof(int));
    // Записываем в файл значение переменной time
    outFile.write(reinterpret_cast<const char*>(&time), sizeof(int));
    // Записываем в файл значение переменной countLines
    outFile.write(reinterpret_cast<const char*>(&countLines), sizeof(int));
    // Записываем в файл значение переменной lines_in_a_row
    outFile.write(reinterpret_cast<const char*>(&lines_in_a_row), sizeof(int));

    // Инициализируем переменную значением ячейки
    int cellValue;
    // Проходим по всем ячейкам игрового поля
    for (int i = 0; i < field.getHeight(); ++i)
    {
        for (int j = 0; j < field.getWidth(); ++j)
        {
            // Получаем значение ячейки
            cellValue = field.getGameBoard(i,j);
            // Записываем значение ячейки в файл
            outFile.write(reinterpret_cast<const char*>(&cellValue), sizeof(int));
        }
    }

    // Закрываем файл
    outFile.close();
}

// Метод для загрузки игры из файла
void Game::loadGameFromFile(std::string fileName)
{
    // Открываем файл в бинарном режиме
    std::ifstream inFile(fileName, std::ios::binary);

    // Если файл не открывается, выводим сообщение об ошибке и выходим из функции
    if (!inFile.is_open())
    {
        std::cerr << "Ошибка открытия файла для чтения данных прошлой игры" << std::endl;
        return;
    }

    // Читаем из файла значение переменной score
    inFile.read(reinterpret_cast<char*>(&score), sizeof(int));
    // Читаем из файла значение переменной fileTime
    inFile.read(reinterpret_cast<char*>(&fileTime), sizeof(int));
    // Читаем из файла значение переменной countLines
    inFile.read(reinterpret_cast<char*>(&countLines), sizeof(int));
    // Читаем из файла значение переменной lines_in_a_row
    inFile.read(reinterpret_cast<char*>(&lines_in_a_row), sizeof(int));
    // Перезапускаем таймер игры
    gameTime.restart();

    // Инициализируем переменную значением ячейки
    int cellValue;
    // Проходим по всем ячейкам игрового поля
    for (int i = 0; i < field.getHeight(); ++i)
    {
        for (int j = 0; j < field.getWidth(); ++j)
        {
            // Читаем значение ячейки из файла
            inFile.read(reinterpret_cast<char*>(&cellValue), sizeof(int));
            // Устанавливаем значение ячейки на игровом поле
            field.setGameBoard(i, j, cellValue);
        }
    }

    // Закрываем файл
    inFile.close();
}

// Деструктор класса Game
Game::~Game()
{
    // Удаляем текущую фигуру
    delete currentFigure;
    // Удаляем следующую фигуру
    delete nextFigure;
    // Удаляем все фигуры из вектора фигур
    for (Figure * figure : figures) {
        delete figure;
    }
    // Очищаем вектор фигур
    figures.clear();
}





