#ifndef TETRIS_GAMEMENU_H
#define TETRIS_GAMEMENU_H

#include "Picture.h"
#include "header.h"
#include "Button.h"
class Game;

// Класс GameMenu объявляет главное меню игры
class GameMenu
{
private:
    // Здесь хранится выбранный пользователем пункт меню
    int selectedMenuOption;
    // Указатель на кнопку в меню
    int key;
    // Объекты класса Button для каждой кнопки на главном экране
    Button buttonStart;
    Button buttonResume;
    Button buttonExit;
    // Объект Picture для отображения главного меню
    Picture mainMenu;
    // Флаг, указывающий, активно ли меню
    bool isMenu;
public:
    // Конструктор
    GameMenu();
    // Отображает меню в окне
    void showMenu(sf::RenderWindow& window, Game& game);
    // Проверяем, нажата ли клавиша
    void keyPressCheck(sf::Event& event);
    // Действие, которое нужно выполнить после нажатия кнопки
    void buttonAction(Game& game);
    // Геттер для поля isMenu
    bool getIsMenu() const;
    // Сеттер для поля isMenu
    void setIsMenu(bool x);
    // Деструктор
    ~GameMenu();
};

#endif //TETRIS_GAMEMENU_H