//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CHAIN_H
#define BEANS_CHAIN_H

#include "iostream"
#include "vector"
#include "../Cards/Card.h"
#include "../CardFactory.h"

using namespace std;

template <class T>
class Chain {
private:
    vector<T*> cards;

public:

    Chain() {

    }

    Chain(istream&, const CardFactory*) {

    }
    Chain<T>& operator+=( Card* card) {
        cards.push_back(card);
    }

    int sell() {
        if (cards.size() <= 0) {
            return 0;
        }

        Card* c = ((Card*)cards[0]);
        //TODO: Fix this

        return 0;
    }

    friend ostream& operator<< (ostream& out, const Chain& chain);

};

template <class T>
ostream& operator<<(ostream &out, const Chain<T> &chain) {

//    Card* type = T();
//    out << type->getName() << "    ";

    // for each card in deck
    for_each(chain.cards.begin(), chain.cards.end(),[&out](const Card* n) {
        // output card name
        out << " " << n->getName();
    });

    out << endl;

    return out;
}


#endif //BEANS_CHAIN_H