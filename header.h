#ifndef TETRIS_HEADER_H
#define TETRIS_HEADER_H

const int WIDTH = 10;
const int HEIGHT = 20;
const int CELL_SIZE = 30;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <fstream>
#include <map>

#include "MyQueue.h"
#include <thread>

#include "Picture.h"
#include "Text.h"
#include "Button.h"
#include "GameMenu.h"
#include "Board.h"
#include "Figure.h"
#include "Exceptions.h"







int generateRandomNumber (int a, int b);



#endif //TETRIS_HEADER_H
