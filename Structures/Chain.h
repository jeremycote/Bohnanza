//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CHAIN_H
#define BEANS_CHAIN_H

#include <iostream>
#include <vector>
#include "../Cards/Card.h"
#include "../CardFactory.h"

using namespace std;

template <class T>
class Chain {
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
            cards.push_back(factory->getInstance()->getUnallocatedCard(w));
        }
    }

    Chain<T>& operator+=(T* card) {
        cards.push_back(card);
        return *this;
    }

    bool chainMatchesType(T* card);

    int sell() {

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

    void save(ostream& out) {
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

    friend ostream& operator<< (ostream& out, const Chain<Card>& chain)  {

        if (chain.cards.empty()) {
            out << "Card:";
        } else {
            out << chain.cards[0]->getName() << ":";
            for(const auto& card: chain.cards) {
                out << " " << *card;
            }
        }

        out << endl;

        return out;
    }

};

template <class T>
bool Chain<T>::chainMatchesType(T *card) {
    return 0;
}

template<>
bool Chain<Card>::chainMatchesType(Card *card) {
    if (cards.size() == 0) {
        return false;
    }

    return cards[0]->getType() == card->getType();
}


#endif //BEANS_CHAIN_H