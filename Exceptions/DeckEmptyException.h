//
// Created by Jeremy Cote on 2022-11-23.
//

#ifndef BEANS_DECKEMPTYEXCEPTION_H
#define BEANS_DECKEMPTYEXCEPTION_H

#include <exception>

/**
 * Exception thrown when the deck is empty
 */
class DeckEmptyException : public std::exception {
    const char * what() const noexcept override {
        return "Deck Empty Exception";
    }
};


#endif //BEANS_DECKEMPTYEXCEPTION_H
