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

#include "Structures/Deck.h"

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

    CardFactory();
public:
    static CardFactory* getInstance() {
        return &instance;
    }
    Deck getDeck();
};

CardFactory CardFactory::instance = CardFactory();


#endif //BEANS_CARDFACTORY_H
