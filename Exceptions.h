#ifndef TETRIS_EXCEPTIONS_H
#define TETRIS_EXCEPTIONS_H
#include <exception>
#include <string>
#include <utility>

class Exceptions: public std::exception
{
protected:
    std::string message;
public:
    Exceptions() = default;

    [[nodiscard]] const char* what() const noexcept override{return message.c_str();}

};

class ExceptionFile: public Exceptions
{
public:
    explicit ExceptionFile(std::string mes)
    {
        message = std::move(mes);
    }
    ExceptionFile() = delete;

};


#endif //TETRIS_EXCEPTIONS_H