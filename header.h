#ifndef TETRIS_HEADER_H
#define TETRIS_HEADER_H

const int WIDTH = 13;
const int HEIGHT = 22;
const int CELL_SIZE = 30;
const int COUNT_PERSONS = 5;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <fstream>
#include <map>


#include <thread>
#include "Sprite.h"
#include "GameMenu.h"
#include "Board.h"
#include "Figure.h"
#include "Exceptions.h"







int generateRandomNumber (int a, int b);

#endif //TETRIS_HEADER_H
