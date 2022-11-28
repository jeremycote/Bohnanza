//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CARDFACTORY_H
#define BEANS_CARDFACTORY_H

#include <random>

#include "Cards/Card.h"
#include "Cards/Blue.h"
#include "Cards/Chili.h"
#include "Cards/Stink.h"
#include "Cards/Green.h"
#include "Cards/Soy.h"
#include "Cards/Black.h"
#include "Cards/Red.h"
#include "Cards/Garden.h"

class Deck;

using namespace std;

class CardFactory {
private:
    static CardFactory instance;

    //Array of pointers to the 104 cards
    Card** cards;
    int nCards = 0;

    /**
     * Create all cards for the system.
     */
    CardFactory() {
        cards = new Card*[Card::getTotalNumber()];

        for (int i = 0; i < Blue::getTotalNumber(); i++) {
            cards[nCards] = new Blue;
            nCards++;
        }
        for (int i = 0; i < Chili::getTotalNumber(); i++) {
            cards[nCards] = new Chili;
            nCards++;
        }
        for (int i = 0; i < Stink::getTotalNumber(); i++) {
            cards[nCards] = new Stink;
            nCards++;
        }
        for (int i = 0; i < Green::getTotalNumber(); i++) {
            cards[nCards] = new Green;
            nCards++;
        }
        for (int i = 0; i < Soy::getTotalNumber(); i++) {
            cards[nCards] = new Soy;
            nCards++;
        }
        for (int i = 0; i < Black::getTotalNumber(); i++) {
            cards[nCards] = new Black;
            nCards++;
        }
        for (int i = 0; i < Red::getTotalNumber(); i++) {
            cards[nCards] = new Red;
            nCards++;
        }
        for (int i = 0; i < Garden::getTotalNumber(); i++) {
            cards[nCards] = new Garden;
            nCards++;
        }

    }
public:
    /**
     * Return reference to CardFactory instance
     * @return
     */
    static CardFactory* getInstance() {
        return &instance;
    }

    /**
     * Return a shuffled deck
     * @return
     */
    Deck getDeck() const;

    /**
     * Get an unallocated card
     * @return
     */
    Card* getUnallocatedCard(string& identifier) const {
        for (int i = 0; i < nCards; i++) {

            if (!cards[i]->getIsAllocated() && cards[i]->getName() == identifier) {
                cards[i]->setIsAllocated(true);
                return cards[i];
            }
        }

        throw out_of_range("There are no unallocated cards with identifier " + identifier);
    }

    /**
     * Reset allocation of all cards
     */
    void resetAllocation() {
        for (int i = 0; i < nCards; i++) {
            cards[i]->setIsAllocated(false);
        }
    }
};

#endif //BEANS_CARDFACTORY_H
