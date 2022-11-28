//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_CARDFACTORY_H
#define BEANS_CARDFACTORY_H

#include "Cards/Card.h"
#include "Cards/Blue.h"
#include "Cards/Chili.h"
#include "Cards/Stink.h"
#include "Cards/Green.h"
#include "Cards/Soy.h"
#include "Cards/Black.h"
#include "Cards/Red.h"
#include "Cards/Garden.h"

#include <random>

class Deck;

using namespace std;

#define N_CARDS 104
#define N_BLUE 20
#define N_CHILI 18
#define N_STINK 16
#define N_GREEN 14
#define N_SOY 12
#define N_BLACK 10
#define N_RED 8
#define N_GARDEN 6

class CardFactory {
private:
    static CardFactory instance;

    //Array of pointers to the 104 cards
    Card** cards;
    int nCards = 0;

    CardFactory() {

        cards = new Card*[N_CARDS];

        for (int i = 0; i < N_BLUE; i++) {
            cards[nCards] = new Blue;
            nCards++;
        }
        for (int i = 0; i < N_CHILI; i++) {
            cards[nCards] = new Chili;
            nCards++;
        }
        for (int i = 0; i < N_STINK; i++) {
            cards[nCards] = new Stink;
            nCards++;
        }
        for (int i = 0; i < N_GREEN; i++) {
            cards[nCards] = new Green;
            nCards++;
        }
        for (int i = 0; i < N_SOY; i++) {
            cards[nCards] = new Soy;
            nCards++;
        }
        for (int i = 0; i < N_BLACK; i++) {
            cards[nCards] = new Black;
            nCards++;
        }
        for (int i = 0; i < N_RED; i++) {
            cards[nCards] = new Red;
            nCards++;
        }
        for (int i = 0; i < N_GARDEN; i++) {
            cards[nCards] = new Garden;
            nCards++;
        }
    }
public:
    static CardFactory* getInstance() {
        return &instance;
    }
    Deck getDeck();

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
