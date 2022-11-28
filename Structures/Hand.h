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

class Hand {
private:
    list<Card*> cards;
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
            cards.push_back(factory->getUnallocatedCard(word));
        }
    }

    Hand& operator+=(Card* card) {
        cards.push_back(card);
        return *this;
    }

    /**
     * Remove and return first card in hand (Queue).
     * @return
     */
    Card* play() {
        // Get the card at the front of the queue
        Card* card = cards.front();

        // Remove the card from the queue
        cards.pop_front();

        // Return the card
        return card;
    }

    /*
     * Return the next card to be played.
     */
    Card* top() {
        return cards.front();
    }

    Card* operator[](int i) {
        auto front = cards.begin();
        advance(front, i);
        return *front;
    }

    int size() {
        return cards.size();
    }

    friend ostream& operator<<(ostream& out, const Hand& hand);
};

ostream& operator<<(ostream& out, const Hand& hand) {

    out << "Hand:";

    for(const auto& card: hand.cards) {
        out << " " << card->getName();
    }

    return out << endl;
}

#endif //BEANS_HAND_H
