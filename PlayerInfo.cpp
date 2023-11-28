#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(const std::string& name, int _score)
        : nickName(name), score(_score) {}

PlayerInfo& PlayerInfo::operator=(const PlayerInfo& obj)
{
    if (&obj != this)
    {
        this->score = obj.score;
        this->nickName = obj.nickName;
    }
    return *this;
}

std::string PlayerInfo::getNickName() const
{
    return nickName;
}

int PlayerInfo::getScore() const
{
    return score;
}

void PlayerInfo::setNickName(const std::string& name)
{
    nickName = name;
}

void PlayerInfo::setScore(int _score)
{
    score = _score;
}