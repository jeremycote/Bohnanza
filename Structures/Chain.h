//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CHAIN_H
#define BEANS_CHAIN_H

#include <iostream>
#include <vector>
#include "../Cards/Card.h"
#include "../CardFactory.h"
#include "ChainBase.h"
#include "../Exceptions/IllegalTypeException.h"
#include <iomanip>

using namespace std;

template <class T>
class Chain : public ChainBase {
private:
    vector<T*> cards;

public:
    /**
     * Default constructor. Constructs an empty chain.
     */
    Chain<T>() = default;

    /**
     * Construct chain from istream.
     * @param in
     * @param factory
     */
    Chain<T>(istream& in, const CardFactory* factory) {
        // Parse istream
        string w;
        string line;

        getline(in, line);

        istringstream ss(line);

        // Parse each word as a card
        while (ss >> w) {
            cards.push_back(dynamic_cast<T*>(factory->getUnallocatedCard(w)));
        }
    }

    /**
     * Insert card into chain.
     * Throws IllegalTypeException if card type does not match.
     * @param card
     * @return
     */
    Chain<T>& operator+=(Card* card) {

        T* c = dynamic_cast<T*>(card);

        if (c == nullptr) {
            throw IllegalTypeException();
        }

        cards.push_back(c);
        return *this;
    }

    /**
     * Returns coin value of the chain
     * @return
     */
    int sell() override {

        int s = cards.size();

        // If there are no cards, the value is zero
        if (s == 0) {
            return 0;
        }

        Card* c = dynamic_cast<Card*>(cards[0]);

        // Call getCardsPerCoin starting with largest amount until valid int found
        int i = 4;
        while (i > 0) {

            if (c->getCardsPerCoin(i) <= s) {
                return c->getCardsPerCoin(i);
            }

            i--;
        }

        return 0;
    }

    /**
     * Write contents of chain into ostream.
     * @param out
     */
    void save(ostream& out) override {
        if (cards.empty()) {
            out << "Card:";
        } else {
            out << cards[0]->getName() << ":";
            for(const auto& card: cards) {
                out << " " << card->getName();
            }
        }
        out << endl;
    }

    /**
     * Write human readable contents of chain.
     * Method will be called by {@link ChainBase} for >> operator.
     * @param out
     */
    void print(ostream& out) const override {

        if (cards.empty()) {
            out << "Card:";
        } else {
            out << cards[0]->getName() << ":";

            out << setw(spacer + (longestLabel - cards[0]->getName().size()));
            for(const auto& card: cards) {
                out << " " << *card;
            }
        }

        out << endl;
    }
};

#endif //BEANS_CHAIN_H