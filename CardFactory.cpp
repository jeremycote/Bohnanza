//
// Created by Jeremy Cote on 2022-11-15.
//

#include "CardFactory.h"
#include "Structures/Deck.h"

Deck CardFactory::getDeck() const {
    // Instantiate deck
    Deck deck;

    std::random_device dev;
    shuffle(cards, cards + nCards, default_random_engine(dev.entropy()));

    for (int i = 0; i < nCards; i++) {
        deck.push_back(cards[i]);
        cards[i]->setIsAllocated(false);
    }

    return deck;
}