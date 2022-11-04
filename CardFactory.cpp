//
// Created by Jeremy Cote on 2022-11-04.
//

#include "CardFactory.h"

/**
 * Create a CardFactory by instantiating cards of necessary types
 */
CardFactory::CardFactory() {

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

/**
 * Instantiate a new Deck with pointers to CardFactory's cards
 * @return
 */
Deck CardFactory::getDeck() {
    // Instantiate deck
    Deck deck;

    for (int i = 0; i < nCards; i++) {
        deck.push_back(cards[i]);
    }

    return deck;
}