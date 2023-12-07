#ifndef TETRIS_EXCEPTIONS_H
#define TETRIS_EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>

// Класс Exceptions представляет базовые исключения в этом проекте.
// Наследуется от стандартного класса std::exception
class Exceptions: public std::exception
{
protected:
    std::string message;  // сообщение исключения
public:
    Exceptions() = default;

    // what() возвращает сообщение об исключении
    [[nodiscard]] const char* what() const noexcept override{return message.c_str();}
};

// Класс ExceptionFile представляет исключения, связанные с файлами.
class ExceptionFile: public Exceptions
{
public:
    explicit ExceptionFile(std::string mes)
    {
        message = std::move(mes);
    }
    ExceptionFile() = delete;
};

// Класс ExceptionSFML представляет исключения, связанные с библиотекой SFML.
class ExceptionSFML: public Exceptions
{
public:
    explicit ExceptionSFML(std::string mes)
    {
        message = std::move(mes);
    }
    ExceptionSFML() = delete;
};

// Класс OutOfBoundsException представляет исключения для случаев, когда
// происходит выход за пределы массива или списка.
class OutOfBoundsException: public Exceptions
{
public:
    explicit OutOfBoundsException(std::string mes)
    {
        message = std::move(mes);
    }
    OutOfBoundsException() = delete;
};


#endif //TETRIS_EXCEPTIONS_H