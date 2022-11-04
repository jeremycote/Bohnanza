//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_BLACK_H
#define BEANS_BLACK_H

#include "Card.h"

class Black : Card {
public:
    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 2;
            case 2:
                return 4;
            case 3:
                return 5;
            case 4:
                return 6;
            default:
                return 0;
        }
    };
    string getName() const override {
        return "Black";
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };
};

#endif //BEANS_BLACK_H
