//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_DECK_H
#define BEANS_DECK_H

#include "iostream"
#include "vector"
#include "../Cards/Card.h"

using namespace std;

class Deck : public vector<Card*> {
public:
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
    for_each(deck.begin(), deck.end(),[&out](const Card* n) {
        // output card name
        out << n->getName();
    });

    return out;
}

#endif //BEANS_DECK_H
