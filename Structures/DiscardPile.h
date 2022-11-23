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

class DiscardPile : public vector<Card*> {
public:

    /**
     * Constructor for creating an empty discard pile
     */
    DiscardPile() {

    }

    /**
     * Constructor for creating a discard pile from istream
     * @param in
     * @param factory
     */
    DiscardPile(istream& in, CardFactory* factory) {
        string word;
        while (in >> word) {
            push_back(factory->getUnallocatedCard(word));
        }
    }

    /**
     * Add a card to the discard pile
     * @param card
     * @return
     */
    DiscardPile &operator+=(Card *card) {
        push_back(card);
        return *this;
    }

    /**
     * Return the top card of the discard pile and remove it from the discard pile.
     * @return
     */
    Card *pickUp() {
        // Get the last card
        Card *card = back();

        // Remove the last card from the deck
        pop_back();

        return card;
    }

    /**
     * Returns the top card of the discard pile
     * @return
     */
    Card *top() const {
        return back();
    }

    void print(ostream &out) const {

        out << "DiscardPile:";

        for(const auto& card: *this) {
            out << " " << card->getName();
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

    out << *pile.top();

    return out;
}

#endif //BEANS_DISCARDPILE_H
