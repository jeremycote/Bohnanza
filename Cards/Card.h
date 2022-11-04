//
// Created by Jeremy Cote on 2022-11-03.
//

#ifndef BEANS_CARD_H
#define BEANS_CARD_H

#include <string>
#include <iostream>

using namespace std;

class Card {
public:
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual string getName() const = 0;
    virtual void print(ostream& out) const = 0;
};

#endif //BEANS_CARD_H
