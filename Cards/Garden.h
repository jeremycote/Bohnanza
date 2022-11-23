//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_GARDEN_H
#define BEANS_GARDEN_H

#include "Card.h"

class Garden : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        switch (coins) {
            case 2:
                return 2;
            case 3:
                return 3;
            default:
                return 100;
        }
    };
    string getName() const override {
        return "Garden";
    };
    void print(ostream& out) const override {
        out << getName()[0];
    };
    virtual CardType getType() const {
        return GardenType;
    };
};

#endif //BEANS_GARDEN_H
