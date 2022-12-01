//
// Created by Jeremy Cote on 2022-11-23.
//

#ifndef BEANS_ILLEGALTYPEEXCEPTION_H
#define BEANS_ILLEGALTYPEEXCEPTION_H

#include <exception>

/**
 * Exception thrown when Card casting fails
 */
class IllegalTypeException : public std::exception {
    const char * what() const noexcept override {
        return "Illegal Type Exception";
    }
};


#endif //BEANS_ILLEGALTYPEEXCEPTION_H
