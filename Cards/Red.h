//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_RED_H
#define BEANS_RED_H

#include "Card.h"

class Red : public Card {
public:
    const static string name;

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
                return 100;
        }
    };
    string getName() const override {
        return name;
    };
    void print(ostream& out) const override {
        out << getName()[0];
    }

    static int getTotalNumber() {
        return 8;
    }
};

#endif //BEANS_RED_H
