//
// Created by Jeremy Cote on 2022-11-03.
//

#ifndef BEANS_CARD_H
#define BEANS_CARD_H

#include <string>
#include <iostream>

using namespace std;

class Card {
private:
    Card(Card& o) = default;
    Card& operator=(Card& o) = default;
    bool isAllocated = false;
public:
    Card() = default;

    virtual int getCardsPerCoin(int coins) const = 0;
    virtual string getName() const = 0;
    virtual void print(ostream& out) const = 0;

    friend ostream& operator<< (ostream& out, const Card& card)  {
        card.print(out);
        return out;
    }

    bool getIsAllocated() const {
        return isAllocated;
    }

    void setIsAllocated(const bool& allocate) {
        this->isAllocated = allocate;
    }

    static int getTotalNumber() {
        return 104;
    }
};

#endif //BEANS_CARD_H
