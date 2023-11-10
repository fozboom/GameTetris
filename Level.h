#ifndef TETRIS_LEVEL_H
#define TETRIS_LEVEL_H


class Level
{
protected:
    int level;
    int blockSpeed;
    int numBlocks;
public:
    Level(int lvl, int speed, int blocks) : level(lvl), blockSpeed(speed), numBlocks(blocks) {}


    int getLevel() const { return level; }
    int getBlockSpeed() const { return blockSpeed; }
    int getNumBlocks() const { return numBlocks; }
};


class EasyLevel : public Level {
public:
    EasyLevel() : Level(1, 1, 10) {}
};


class MediumLevel : public Level {
public:
    MediumLevel() : Level(2, 2, 15) {}
};


class HardLevel : public Level {
public:
    HardLevel() : Level(3, 3, 20) {}
};


#endif //TETRIS_LEVEL_H
