#include "GameMenu.h"
#include "Game.h"

// Конструктор класса GameMenu. В нем инициализируются изображения для главного меню и кнопок, а также устанавливаются начальные значения переменных
GameMenu::GameMenu():
        mainMenu("images/mainMenu.png", 0, 0),
        buttonStart("Start", 286,127,"images/buttonStart.png", 579,233),
        buttonResume("Resume", 286, 127,"images/buttonResume.png", 579,395),
        buttonExit("Exit", 286, 127,"images/buttonExit.png", 579, 554),
        selectedMenuOption(0), key(0), isMenu(true)
{

}

// Деструктор класса GameMenu
GameMenu::~GameMenu() {

}

// Функция проверяет, была ли нажата кнопка на клавиатуре
void GameMenu::keyPressCheck(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            key = 1; // Если нажата клавиша "вверх", устанавливается key = 1
        }
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            key = 2; // Если нажата клавиша "вниз", ключ будет равен 2
        }
        if (event.key.code == sf::Keyboard::Enter)
        {
            key = 3; // Если нажат enter, ключ устанавливается равным 3
        }
    }
}

// Функция отвечает за отображение главного меню
void GameMenu::showMenu(sf::RenderWindow& window, Game& game)
{
    // Отображение картинок для каждой кнопки и главного меню
    window.draw(mainMenu.sprite);
    window.draw(buttonStart.sprite);
    window.draw(buttonResume.sprite);
    window.draw(buttonExit.sprite);

    // Выполняет действие, связанное с нажатием кнопки
    buttonAction(game);

    // В зависимости от текущего выбранного пункта меню обновляем спрайты кнопок
    if (selectedMenuOption == 0)
    {
        buttonStart.updateSprite("images/selectedStart.png");
        buttonResume.updateSprite("images/buttonResume.png");
        buttonExit.updateSprite("images/buttonExit.png");
    }
    else if (selectedMenuOption == 1)
    {
        buttonStart.updateSprite("images/buttonStart.png");
        buttonResume.updateSprite("images/selectedResume.png");
        buttonExit.updateSprite("images/buttonExit.png");
    }
    else
    {
        buttonStart.updateSprite("images/buttonStart.png");
        buttonResume.updateSprite("images/buttonResume.png");
        buttonExit.updateSprite("images/selectedExit.png");
    }
}

// Функция определяет какое действие нужно выполнить при нажатии кнопки
void GameMenu::buttonAction(Game& game)
{
    if (key == 1)
    {
        selectedMenuOption--; // Перемещаемся вверх по меню
        if (selectedMenuOption < 0)
            selectedMenuOption = 2;
        buttonResume.playMusic(); // Воспроизводим музыку
    }
    if (key == 2)
    {
        selectedMenuOption++; // Перемещаемся вниз по меню
        if (selectedMenuOption > 2)
            selectedMenuOption = 0;
        buttonResume.playMusic(); // Воспроизводим музыку
    }
    if (key == 3) // Если нажат enter
    {
        buttonResume.playMusic(); // Воспроизводим музыку
        if (selectedMenuOption == 0)
            isMenu = false; // Выходим из меню, если выбран пункт "Start"
        else if (selectedMenuOption == 1)
        {
            game.loadGameFromFile("Game"); // Загружаем игру из файла, если выбран пункт "Resume"
            isMenu = false;
        }
        else
        {
            exit(EXIT_SUCCESS); // Выходим из игры, если выбран пункт "Exit"
        }
    }
    key = 0; // Сбрасываем ключ
}

// Геттер для флага isMenu
bool GameMenu::getIsMenu() const
{
    return isMenu;
}

// Сеттер для флага isMenu
void GameMenu::setIsMenu(bool x)
{
    isMenu = x;
}