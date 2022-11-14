//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_DISCARDPILE_H
#define BEANS_DISCARDPILE_H

#include "iostream"
#include "vector"
#include "../Cards/Card.h"
#include "../CardFactory.h"

using namespace std;

class DiscardPile {
private:
    vector<Card *> cards;
public:

    DiscardPile(istream& in, const CardFactory* factory) {

    }

    /**
     * Add a card to the discard pile
     * @param card
     * @return
     */
    DiscardPile &operator+=(Card *card) {
        cards.push_back(card);
        return *this;
    }

    /**
     * Return the top card of the discard pile and remove it from the discard pile.
     * @return
     */
    Card *pickUp() {
        // Get the last card
        Card *card = cards.back();

        // Remove the last card from the deck
        cards.pop_back();

        return card;
    }

    /**
     * Returns the top card of the discard pile
     * @return
     */
    Card *top() const {
        return cards.back();
    }

    void print(ostream &out) const {

        out << "DiscardPile:";

        for(const auto& card: cards) {
            out << " " << card;
        }

        out << endl;
    }

    /**
     * Insert the top card of the pile into an ostream
     * @param out
     * @param pile
     * @return
     */
    friend ostream& operator<<(ostream& out, const DiscardPile& pile);
};

ostream& operator<<(ostream& out, const DiscardPile& pile) {

    out << pile.top();

    return out;
}

#endif //BEANS_DISCARDPILE_H
