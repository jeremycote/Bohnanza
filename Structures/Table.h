//
// Created by Jeremy Cote on 2022-11-07.
//

#ifndef BEANS_TABLE_H
#define BEANS_TABLE_H

#include <iostream>
#include <sstream>
#include <string>
#include "../Player.h"
#include "../Structures/DiscardPile.h"
#include "../Structures/TradeArea.h"
#include "../Constants.h"

using namespace std;

class Table {
private:
    Player *p1;
    Player *p2;

    Deck deck;
    DiscardPile *discardPile;
    TradeArea *tradeArea;

public:
    Table(istream& in, const CardFactory*) {
        char line[256];
        in.getline(line, 256);

        // Compare if first line of input stream is default string
//        if (strcmp(line, defaultCString) == 0) {
            string p1Name;
            string p2Name;

            cout << "Enter P1 Name: ";
            cin >> p1Name;
            cout << endl << "Enter P2 Name: ";
            cin >> p2Name;
            cout << endl;

            p1 = new Player(p1Name);
            p2 = new Player(p2Name);

            deck = CardFactory::getInstance()->getDeck();

            for (int i = 0; i < startingHandSize; i++) {
                p1->getHand() += deck.draw();
                p2->getHand() += deck.draw();
            }

            discardPile = new DiscardPile(in, CardFactory::getInstance());
//        } else {
//        }
    }

    /**
     * Check if deck is empty and player has more coins than adversary.
     * Returns true only if deck is empty and player has more coins than opponent.
     * @param playerName
     * @return
     */
    bool win(string& playerName) {
        if (deck.empty() && p1->getNumCoins() != p2->getNumCoins()) {

            Player *winner = p1->getNumCoins() > p2->getNumCoins() ? p1 : p2;

            return winner->getName() == playerName;
        }

        return false;
    }

    void printHand(bool entireHand) {
//        currentPlayer->printHand(cout, entireHand);
    }

    void saveTable(ostream* out) {

    }

    friend ostream& operator<< (ostream& out, const Table& table);
};

ostream& operator<<(ostream &out, const Table &table) {



    return out;
}

#endif //BEANS_TABLE_H
