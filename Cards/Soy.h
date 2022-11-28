//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_SOY_H
#define BEANS_SOY_H

#include "Card.h"

class Soy : public Card {
public:
    const static string name;

    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 2;
            case 2:
                return 4;
            case 3:
                return 6;
            case 4:
                return 7;
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
        return 12;
    }
};

#endif //BEANS_SOY_H
