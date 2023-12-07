#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H


#include "header.h"
#include "Board.h"
#include "Figure.h"
#include "Button.h"
#include "Picture.h"
#include "Queue.h"
#include "GameMenu.h"

class Game  // Определение класса Game
{
// Защищенные (доступны только внутри данного класса и классов-наследников) атрибуты класса:
protected:
    Board field;  // Игровое поле
    Figure* currentFigure;  // Текущая фигура
    Figure* nextFigure;  // Следующая фигура
    std::vector<Figure*> figures;  // Вектор фигур

    Button buttonPause;  // Кнопка паузы
    Button buttonRestart;  // Кнопка перезагрузки
    Button buttonMusic;  // Кнопка музыки

    Picture buttonGameOver;  // Кнопка окончания игры
    Picture buttonRowsCount;  // Кнопка подсчета счёта
    Picture oneBlock;  // Один блок
    Picture pauseBoard;  // Изображение доски при паузе

    sf::Font font;  // Шрифт
    sf::Text text;  // Текст
    sf::Clock gameTime;  // Часы игрового времени
    sf::Music music;  // Музыка

    int lines_in_a_row;  // Количество линий в ряду
    int score;  // Счет
    int time;  // Время
    int fileTime;  // Временной файл
    int tmpTime;  // Временное время
    int countLines;  // Счётчик линий
    std::string number;  // Номер
    std::string nickName;  // Имя игрока

    Queue<PlayerInfo> infoQueue;  // Очередь с информацией об игроках
public:

public:
    Game();  // Конструктор класса Game
    // Основные функции класса:
    int keyPressCheck(sf::Event& event, sf::RenderWindow& window, int& key, GameMenu& menu);  // Функция проверки нажатия клавиши
    int mousePressedCheck(sf::Event& event, sf::RenderWindow& window);  // Функция проверки нажатия мыши
    void buttonAction (int& key);  // Функция действия кнопки
    void fallingFigure (sf::Clock& timer, float pause);  // Функция падения фигуры
    Figure* getRandomFigure();  // Функция получения случайной фигуры
    void getAllFigures();  // Функция получения всех фигур
    void drawBoardImage (sf::RenderWindow& window);  // Функция отрисовки изображения доски
    void draw(sf::RenderWindow& window);  // Основная функция отрисовки
    void drawNextFigureBlock(sf::RenderWindow& window);  // Функция отрисовки блока следующей фигуры
    bool boundariesIsBroken ();  // Функция проверки нарушения границ
    void isLocked();  // Функция проверки блокировки
    int distanceToLocked ();  // Функция расчёта расстояния до блокировки
    void drawPlacedBlocks(sf::RenderWindow& window);  // Функция отрисовки размещенных блоков
    bool gameOver(sf::RenderWindow& window, sf::Event& event);  // Функция окончания игры
    void checkAndClearFilledLines ();  // Функция проверки и очистки заполненных линий
    void deleteLine (int num, int count);  // Функция удаления линии
    void readFileBestPlayers(const char* fileName);  // Функция чтения файла с лучшими игроками
    void writeFileBestPlayers(const char* fileName);  // Функция записи в файл лучших игроков
    void showBestPlayersBlock(sf::RenderWindow& window);  // Функция отображения блока с лучшими игроками
    void scoreBooster (int& _lines_in_a_row);  // Функция увеличения счета
    void showGameTime(sf::RenderWindow& window);  // Функция отображения игрового времени
    void showScore (sf::RenderWindow& window);  // Функция отображения счета
    void checkStatisticBeforeSave();  // Функция проверки статистики перед сохранением
    bool processGameCycle (sf::RenderWindow& window, GameMenu& menu);  // Функция обработки игрового цикла
    void loadGameFromFile(std::string fileName);  // Функция загрузки игры из файла
    void saveGameToFile(std::string fileName);  // Функция сохранения игры в файл
    void getStartBoxOfFigure();  // Функция получения начальной позиции фигуры
    ~Game();  // Деструктор класса Game
};

#endif //TETRIS_GAME_H