//
// Created by Jeremy Cote on 2022-11-15.
//

#include "CardFactory.h"
#include "Structures/Deck.h"

Deck CardFactory::getDeck() {



    // Instantiate deck
    Deck deck;

    shuffle(cards, cards + nCards, default_random_engine(0));

    for (int i = 0; i < nCards; i++) {
        deck.push_back(cards[i]);
        cards[i]->setIsAllocated(true);
    }

    return deck;
}