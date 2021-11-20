
#include <iostream>

#ifndef WAREHOUSE_PROJECT_EXCEPTIONS_H
#define WAREHOUSE_PROJECT_EXCEPTIONS_H


struct ChooseError {
    std::string message;
    explicit ChooseError(std::string msg) : message(std::move(msg)) {}
};

struct NotDigitError: public ChooseError {
    explicit NotDigitError(): ChooseError("The specified characters are not a number!") {}
};

struct IDError: public ChooseError {
    explicit IDError(): ChooseError("The ID provided is incorrect!") {}
};


#endif //WAREHOUSE_PROJECT_EXCEPTIONS_H
