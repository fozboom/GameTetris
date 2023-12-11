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
        Button.cpp
        Button.h
        Button.cpp
        Button.h
        Exceptions.h
        GameMenu.cpp
        GameMenu.h
        Text.cpp
        Text.h
        PlayerInfo.h
        Picture.cpp
        Picture.h
        PlayerInfo.cpp
        Queue.h
        List.h
)

target_link_libraries(Tetris sfml-graphics sfml-audio)
