#ifndef TETRIS_HEADER_H
#define TETRIS_HEADER_H

const int WIDTH = 13;
const int HEIGHT = 22;
const int CELL_SIZE = 30;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
//#include <vector>
#include <map>
#include <thread>
#include "Sprite.h"
#include "Board.h"
#include "Figure.h"


int generateRandomNumber (int a, int b);

#endif //TETRIS_HEADER_H
