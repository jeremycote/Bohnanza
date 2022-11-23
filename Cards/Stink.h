//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_STINK_H
#define BEANS_STINK_H

#include "Card.h"

class Stink : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 3;
            case 2:
                return 5;
            case 3:
                return 7;
            case 4:
                return 8;
            default:
                return 100;
        }
    };
    string getName() const override {
        return "Stink";
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };
    virtual CardType getType() const override {
        return StinkType;
    };
};

#endif //BEANS_STINK_H
