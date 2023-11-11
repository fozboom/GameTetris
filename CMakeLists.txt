cmake_minimum_required(VERSION 3.25)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Tetris main.cpp
        Board.h
        Board.cpp
        Game.h
        Game.cpp
        Figure.h
        Figure.cpp
        header.h
        Level.cpp
        Level.h
        Button.cpp
        Button.h
        Sprite.h
        Button.cpp
        Button.h
        Exceptions.h)

target_link_libraries(Tetris sfml-graphics sfml-audio)
