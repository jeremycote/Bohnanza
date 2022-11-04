//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_RED_H
#define BEANS_RED_H

#include "Card.h"

class Red : Card {
public:
    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 2;
            case 2:
                return 3;
            case 3:
                return 4;
            case 4:
                return 5;
            default:
                return 0;
        }
    };
    string getName() const override {
        return "Red";
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };
};

#endif //BEANS_RED_H
