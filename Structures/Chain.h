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
    static const type_info& cardType;

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

        const type_info& i = typeid(T);
        const char* name = i.name();

        if (i == cardType) {
            out << "Card:";
        } else {

            int c = 0;
            while (name[c] != '\0') {
                if (c > 1) {
                    out << name[c];
                }

                c++;
            }
            out << ": ";

            for(const auto& card: chain.cards) {
                out << " " << *card;
            }
        }

        out << endl;

        return out;
    }

};

template <class T>
const type_info& Chain<T>::cardType = typeid(Card);


#endif //BEANS_CHAIN_H