//
// Created by Jeremy Cote on 2022-11-04.
//

#include "Chain.h"

Chain& Chain::operator+=( Card* card) {
    cards.push_back(card);
}

int Chain::sell() {
    if (cards.size() <= 0) {
        return 0;
    }

    Card* c = ((Card*)cards[0]);
    //TODO: Fix this

    return 0;
}

ostream& operator<<(ostream &out, const Chain &chain) {
    // for each card in deck
    for_each(chain.cards.begin(), chain.cards.end(),[&out](const Card* n) {
        // output card name
        out << n->getName() << endl;
    });

    return out;
}
