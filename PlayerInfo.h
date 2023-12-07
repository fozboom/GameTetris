#ifndef TETRIS_PLAYERINFO_H
#define TETRIS_PLAYERINFO_H
#include <iostream>

// класс PlayerInfo содержит информацию об игроке
class PlayerInfo
{
private:
    std::string nickName; // никнейм игрока
    int score; // счет игрока
public:
    // Конструктор PlayerInfo принимает строку никнейма и целое число счета
    PlayerInfo(const std::string& name = "", int _score = 0);

    // Переопределение оператора присваивания для объектов класса PlayerInfo
    PlayerInfo& operator=(const PlayerInfo& obj);

    // Геттер для имени пользователя
    std::string getNickName() const;
    // Геттер для очков пользователя
    int getScore() const;

    // сеттер для имени пользователя
    void setNickName(const std::string& name);
    // сеттер для очков пользователя
    void setScore(int _score);
};

#endif //TETRIS_PLAYERINFO_H