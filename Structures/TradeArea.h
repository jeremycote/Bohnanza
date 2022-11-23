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
    /**
     * Constructor for creating an empty trade area
     */
    TradeArea() {

    }

    /**
     * Constructor for creating a trade area from istream
     */
    TradeArea(istream& in, CardFactory* factory) {
        string word;
        while (in >> word) {
            cards.push_back(factory->getUnallocatedCard(word));
        }
    }

    TradeArea& operator+=(Card* card) {
        cards.push_back(card);
        return *this;
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

        if (!tradeArea.cards.empty()) {
            for(const auto& card: tradeArea.cards) {
                out << " " << card->getName();
            }
        }

        return out << endl;
    }
};

#endif //BEANS_TRADEAREA_H
