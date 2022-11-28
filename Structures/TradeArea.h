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
    TradeArea() = default;

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
        return any_of(cards.begin(), cards.end(), [card](const auto& c){
            return c->getName() == card->getName();
        });
    }

    /**
     * Returns true if trade area contains card with name
     * @param cardName
     * @return
     */
    bool contains(const string& cardName) {
        // Iterate over cards, return true if any of them have the correct name
        return any_of(cards.begin(), cards.end(), [cardName](const auto& card){
            return card->getName() == cardName;
        });
    }

    Card* trade(const string& cardName) {
        auto cardIterator = cards.begin();
        while (cardIterator != cards.end())
        {
            if ((*cardIterator)->getName() == cardName) {
                Card* card = *cardIterator;
                cards.erase(cardIterator);
                return card;
            }

            cardIterator++;
        }

        throw out_of_range("Card not found");
    }

    /**
     * Get first card. Used for discarding.
     * @return
     */
    Card* getCard() {
        auto cardIterator = cards.begin();
        while (cardIterator != cards.end())
        {
            Card* card = *cardIterator;
            cards.erase(cardIterator);
            return card;
        }

        throw out_of_range("Card not found");
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
