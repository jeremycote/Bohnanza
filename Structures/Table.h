//
// Created by Jeremy Cote on 2022-11-07.
//

#ifndef BEANS_TABLE_H
#define BEANS_TABLE_H

#include <string>
#include "../Player.h"

using namespace std;

class Table {
private:
    Player* p1;
    Player* p2;

    Player* currentPlayer;
public:

    Table() {

    }

    Table(istream&, const CardFactory*) {

    }

    bool win(string& playerName) {
        return false;
    }

    void printHand(bool entireHand) {
        currentPlayer->printHand(cout, entireHand);
    }

    friend ostream& operator<< (ostream& out, const Table& table);
};

ostream& operator<<(ostream &out, const Table &table) {
    return out;
}

#endif //BEANS_TABLE_H
