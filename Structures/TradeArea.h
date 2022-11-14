//
// Created by Jeremy Cote on 2022-11-07.
//

#ifndef BEANS_TRADEAREA_H
#define BEANS_TRADEAREA_H

#include "list"

#include "../Cards/Card.h"
#include "../CardFactory.h"

using namespace std;

class TradeArea {
    list<Card*> cards;

public:
    TradeArea() {

    }

    TradeArea(istream&, const CardFactory*) {

    }

    TradeArea& operator+=(Card* card) {

    }

    bool legal(Card* card) {

    }

    Card* trade(string cardName) {

    }

    int numCards() {
        return cards.size();
    }

    friend ostream& operator<< (ostream& out, const TradeArea& tradeArea) {
        out << "TradeArea:";
        for(const auto& card: tradeArea.cards) {
            out << " " << card;
        }
        return out << endl;
    }
};

#endif //BEANS_TRADEAREA_H
