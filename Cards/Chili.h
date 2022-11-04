//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CHILI_H
#define BEANS_CHILI_H

#include "Card.h"

class Chili : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 3;
            case 2:
                return 6;
            case 3:
                return 8;
            case 4:
                return 9;
            default:
                return 0;
        }
    };
    string getName() const override {
        return "Chili";
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };
};

#endif //BEANS_CHILI_H
