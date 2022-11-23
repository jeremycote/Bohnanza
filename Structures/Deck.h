//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_DECK_H
#define BEANS_DECK_H

#include "iostream"
#include "vector"
#include "../CardFactory.h"
#include "../Cards/Card.h"

using namespace std;

class CardFactory;

class Deck : public vector<Card*> {
public:

    /**
     * Constructor for creating a new deck
     */
    Deck() = default;

    /**
     * Constructor for creating a deck from istream
     * @param in
     * @param factory
     */
    Deck(istream& in, CardFactory* factory) {
        string word;
        while (in >> word) {
            push_back(factory->getUnallocatedCard(word));
        }
    }

    Card* draw() {
        // Get the last card
        Card* card = back();

        // Remove the last card from the deck
        pop_back();

        return card;
    }

    friend ostream& operator<< (ostream& out, const Deck& deck) {
        // for each card in deck
        out << "Deck:";

        for(const auto& card: deck) {
            out << " " << card->getName();
        }

        return out << endl;
    }
};

#endif //BEANS_DECK_H
