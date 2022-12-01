//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_HAND_H
#define BEANS_HAND_H

#include "iostream"
#include "list"
#include "queue"

#include "../Cards/Card.h"
#include "../CardFactory.h"

using namespace std;

class Hand : public queue<Card*, list<Card*>> {
public:

    /**
     * Constructor for creating an empty hand
     */
    Hand() = default;

    /**
     * Constructor for creating a hand from an istream
     * @param in
     * @param factory
     */
    Hand(istream& in, CardFactory* factory) {
        string word;
        while (in >> word) {
            push(factory->getUnallocatedCard(word));
        }
    }

    Hand& operator+=(Card* card) {
        push(card);
        return *this;
    }

    /**
     * Remove and return first card in hand (Queue).
     * @return
     */
    Card* play() {
        // Get the card at the front of the queue
        Card* card = front();

        // Remove the card from the queue
        pop();

        // Return the card
        return card;
    }

    /*
     * Return the next card to be played.
     */
    Card* top() {
        return front();
    }

    Card* operator[](int i) {

        auto front = c.begin();
        advance(front, i);
        return *front;
    }

    friend ostream& operator<<(ostream& out, const Hand& hand);
};

ostream& operator<<(ostream& out, const Hand& hand) {

    out << "Hand:";

    auto it = hand.c.begin();
    for (it; it != hand.c.end(); ++it) {
        out << " " << (*it)->getName();
    }

    return out << endl;
}

#endif //BEANS_HAND_H
