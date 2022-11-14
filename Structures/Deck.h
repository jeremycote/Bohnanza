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

    Deck() {

    }

    Deck(istream& in, const CardFactory* factory) {

    }

    Card* draw() {
        // Get the last card
        Card* card = back();

        // Remove the last card from the deck
        pop_back();

        return card;
    }

    friend ostream& operator<< (ostream& out, const Deck& deck);
};

ostream& operator<<(ostream& out, const Deck& deck) {
    // for each card in deck
    cout << "Deck:";

    for(const auto& card: deck) {
        out << " " << card;
    }

    return out << endl;
}

#endif //BEANS_DECK_H
