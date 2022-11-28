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

using namespace std;

template <class T>
class Chain : public ChainBase {
private:
    vector<T*> cards;

public:
    Chain<T>() = default;

    Chain<T>(istream& in, const CardFactory* factory) {
        string w;
        string line;

        getline(in, line);

        istringstream ss(line);

        while (ss >> w) {
            cards.push_back(dynamic_cast<T*>(factory->getUnallocatedCard(w)));
        }
    }

    Chain<T>& operator+=(Card* card) {

        T* c = dynamic_cast<T*>(card);

        if (c == nullptr) {
            throw IllegalTypeException();
        }

        cards.push_back(c);
        return *this;
    }

    int sell() override {

        int s = cards.size();

        Card* c = dynamic_cast<Card*>(cards[0]);

        int i = 4;
        while (i > 0) {

            if (c->getCardsPerCoin(i) <= s) {
                return c->getCardsPerCoin(i);
            }

            i--;
        }

        return 0;
    }

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

    void print(ostream& out) const override {

        if (cards.empty()) {
            out << "Card:";
        } else {
            out << cards[0]->getName() << ":";
            for(const auto& card: cards) {
                out << " " << *card;
            }
        }

        out << endl;
    }
};

#endif //BEANS_CHAIN_H