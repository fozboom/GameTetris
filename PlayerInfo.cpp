#include "PlayerInfo.h"

// Конструктор PlayerInfo принимает имя и счет игрока в качестве параметров
PlayerInfo::PlayerInfo(const std::string& name, int _score)
        : nickName(name), score(_score) {}

// Оператор присваивания
PlayerInfo& PlayerInfo::operator=(const PlayerInfo& obj)
{
    // Проверка на самоприсваивание
    if (&obj != this)
    {
        this->score = obj.score;
        this->nickName = obj.nickName;
    }
    return *this;
}

// Геттеры
std::string PlayerInfo::getNickName() const
{
    return nickName;
}

int PlayerInfo::getScore() const
{
    return score;
}

// сеттеры
void PlayerInfo::setNickName(const std::string& name)
{
    nickName = name;
}

void PlayerInfo::setScore(int _score)
{
    score = _score;
}