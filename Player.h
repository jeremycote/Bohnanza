//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_PLAYER_H
#define BEANS_PLAYER_H

#include "string"

#include "Structures/Chain.h"
#include "Structures/Hand.h"

#include "CardFactory.h"

#include "Exceptions/NotEnoughCoinsException.h"

using namespace std;

class Player {
private:
    string name;
    int coins;
    int maxNumChains;
    Chain chains[3]{};
    Hand hand;
public:

    Player(istream& in, CardFactory factory) {

    }

    /**
     * Create player with name
     */
    Player(string& name) {
        this->name = name;
        maxNumChains = 2;
    }

    /**
     * Return player's name
     * @return
     */
    string getName() {
        return name;
    }

    /**
     * Return the number of coins held by player
     * @return
     */
    int getNumCoins() {
        return coins;
    }

    /**
     * Add n coins to player's total
     * @param nCoins
     * @return
     */
    Player& operator+=(int nCoins) {
        coins += nCoins;
        return *this;
    }

    /**
     * Return max number of chains. (Either 2 or 3)
     * @return
     */
    int getMaxNumChains() {
        return maxNumChains;
    }

    /**
     * Return Chain at position i
     * @param i
     * @return
     */
    Chain& operator[](int i) {
        if (i < 0 || i >= maxNumChains) {
            throw out_of_range("Index is out of range!");
        }

        return chains[i];
    }

    /**
     * Increment maxNumChains to 3. Consumes 2 coins.
     */
    void buyThirdChain() {
        if (maxNumChains == 2) {
            if (coins >= 2) {
                coins -= 2;
                maxNumChains = 3;
            } else {
                // Not enough coins
                throw NotEnoughCoinsException();
            }
        }
    }

    void printHand(ostream& out, bool entireHand) {
        if (entireHand) {
            out << hand << endl;
        } else {
            out << hand.top() << endl;
        }
    }
};


#endif //BEANS_PLAYER_H
