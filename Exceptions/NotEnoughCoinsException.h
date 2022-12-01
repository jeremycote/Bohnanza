//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_NOTENOUGHCOINSEXCEPTION_H
#define BEANS_NOTENOUGHCOINSEXCEPTION_H

#include <exception>

/**
 * Exception thrown when the user does not have enough coins to complete action.
 */
class NotEnoughCoinsException : public std::exception {
    const char * what() const noexcept override {
        return "Not Enough Coins Exception";
    }
};

#endif //BEANS_NOTENOUGHCOINSEXCEPTION_H
