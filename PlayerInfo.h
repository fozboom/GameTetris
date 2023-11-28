#ifndef TETRIS_PLAYERINFO_H
#define TETRIS_PLAYERINFO_H
#include <iostream>

struct PlayerInfo
{
    std::string nickName;
    int score;

public:
    PlayerInfo& operator = (const PlayerInfo& obj)
    {
        this->score = obj.score;
        this->nickName = std::move(obj.nickName);
        return *this;
    }
    PlayerInfo(std::string name = "", int _score = 0): nickName(std::move(name)), score(_score) {};
};
#endif //TETRIS_PLAYERINFO_H
