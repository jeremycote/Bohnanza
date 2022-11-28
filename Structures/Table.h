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
    Player p1;
    Player p2;

    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;

    Player* currentPlayer;

public:

    /**
     * Constructor for creating an empty table
     */
    Table() {

        string p1Name;
        string p2Name;

        cin.ignore();

        cout << "Enter P1 Name: ";
        getline(cin, p1Name);
        cout << endl;


        cout << endl << "Enter P2 Name: ";
        getline(cin, p2Name);
        cout << endl;

        p1 = Player(p1Name);
        p2 = Player(p2Name);

        // Start a new game by using default constructors
        deck = CardFactory::getInstance()->getDeck();
        discardPile = DiscardPile();
        tradeArea = TradeArea();

        for (int i = 0; i < 5; i++) {
            p1.getHand() += deck.draw();
            p2.getHand() += deck.draw();
        }
    }

    /**
     * Constructor for creating a table from istream
     * @param in
     */
    Table(istream& in, const CardFactory* factory) {

        string word;
        string line;
        istringstream *ss;

        // Resume a game by using istream constructors
        p1 = Player(in, CardFactory::getInstance());
        p2 = Player(in, CardFactory::getInstance());

        getline(in, line);

        ss = new istringstream(line);
        *ss >> word;

        deck = Deck(*ss, CardFactory::getInstance());

        delete ss;

        getline(in, line);
        ss = new istringstream(line);
        *ss >> word;

        discardPile = DiscardPile(*ss, CardFactory::getInstance());

        delete ss;

        getline(in, line);
        ss = new istringstream(line);
        *ss >> word;

        tradeArea = TradeArea(*ss, CardFactory::getInstance());
    }

    /**
     * Check if deck is empty and player has more coins than adversary.
     * Returns true only if deck is empty and player has more coins than opponent.
     * @param playerName
     * @return
     */
    bool win(const string& playerName) {
        if (deck.empty() && p1.getNumCoins() != p2.getNumCoins()) {
            return (p1.getNumCoins() > p2.getNumCoins() ? p1 : p2).getName() == playerName;
        }

        return false;
    }

    void printHand(bool entireHand) {
        currentPlayer->printHand(cout, entireHand);
    }

    void saveTable(ostream& out) {
        p1.print(out, true);
        p1.printHand(out, true);
        p2.print(out, true);
        p2.printHand(out, true);
        out << deck;
        discardPile.print(out);
        out << tradeArea;
    }

    friend ostream& operator<< (ostream& out, const Table& table){
        table.p1.print(out);
        table.p2.print(out);
        table.discardPile.print(out);
        out << endl << table.tradeArea << endl;
        return out;
    }

    Deck* getDeck() {
        return &deck;
    }

    DiscardPile* getDiscardPile() {
        return &discardPile;
    }

    TradeArea* getTradeArea() {
        return &tradeArea;
    }

    Player* getPlayer(int idx) {
        if (idx < 0 || idx > 2) {
            throw out_of_range("Player index is out of range");
        }

        return idx == 0 ? &p1 : &p2;
    }

    void setCurrentPlayer(Player* p) {
        this->currentPlayer = p;
    }
};

#endif //BEANS_TABLE_H
