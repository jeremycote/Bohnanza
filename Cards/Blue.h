//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_BLUE_H
#define BEANS_BLUE_H

#include "Card.h"

class Blue : public Card {
public:
    const static string name;

    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 1:
                return 4;
            case 2:
                return 6;
            case 3:
                return 8;
            case 4:
                return 10;
            default:
                return 100;
        }
    };
    string getName() const override {
        return name;
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };

    static int getTotalNumber() {
        return 20;
    }
};

#endif //BEANS_BLUE_H
