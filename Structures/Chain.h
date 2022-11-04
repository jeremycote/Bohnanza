//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CHAIN_H
#define BEANS_CHAIN_H

#include "iostream"
#include "vector"
#include "../Cards/Card.h"

using namespace std;

template <typename T>
class Chain {
private:
    vector<T*> cards;

public:
    Chain<T>& operator+=( Card* );
    int sell();
    friend ostream& operator<< (ostream& out, const Chain<T>& chain);

};


#endif //BEANS_CHAIN_H
