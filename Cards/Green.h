//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_GREEN_H
#define BEANS_GREEN_H

#include "Card.h"

class Green : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 3;
            case 2:
                return 5;
            case 3:
                return 6;
            case 4:
                return 7;
            default:
                return 0;
        }
    };
    string getName() const override {
        return "Green";
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };
};

#endif //BEANS_GREEN_H
