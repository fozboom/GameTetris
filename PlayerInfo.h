#ifndef TETRIS_PLAYERINFO_H
#define TETRIS_PLAYERINFO_H
#include <iostream>

class PlayerInfo
{
private:
    std::string nickName;
    int score;
public:
    PlayerInfo(const std::string& name = "", int _score = 0);
    PlayerInfo& operator=(const PlayerInfo& obj);

    std::string getNickName() const;
    int getScore() const;
    void setNickName(const std::string& name);
    void setScore(int _score);
};

#endif //TETRIS_PLAYERINFO_H