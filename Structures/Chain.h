//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CHAIN_H
#define BEANS_CHAIN_H

#include <iostream>
#include <vector>
#include <typeinfo>
#include "../Cards/Card.h"
#include "../CardFactory.h"

using namespace std;

template <class T>
class Chain {
private:
    vector<T*> cards;

public:

    Chain<T>() {
    }

    Chain<T>(istream&, const CardFactory*) {

    }
    Chain<T>& operator+=(Card* card) {

        T* c = dynamic_cast<T*>(card);

        if (c == nullptr) {
            throw bad_cast();
        }

        cards.push_back(c);
        return *this;
    }

    int sell() {
        if (cards.size() <= 0) {
            return 0;
        }

        Card* c = ((Card*)cards[0]);
        //TODO: Fix this

        return 0;
    }
    friend ostream& operator<< (ostream& out, const Chain<T>& chain)  {

        out << typeid(T).name();

        for(const auto& card: chain.cards) {
            out << " " << *card;
        }

        out << endl;

        return out;
    }

};


#endif //BEANS_CHAIN_H