//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_PLAYER_H
#define BEANS_PLAYER_H

#include <string>
#include <iostream>

#include "Constants.h"

#include "Structures/Chain.h"
#include "Structures/Hand.h"

#include "Exceptions/NotEnoughCoinsException.h"

using namespace std;

class Player {
private:
    string name;
    int coins;
    int maxNumChains;
    Chain<Card*> chains[3]{};
    Hand* hand;
    static int maxNameLength;
public:

    Player(istream& in, CardFactory* factory) {
        hand = new Hand(in, factory);

        char* dest = new char[maxNameLength];
        in.get(dest, maxNameLength, ' ');
        name = string(dest);
    }

    /**
     * Create player with name
     */
    explicit Player(string& name) {

        this->name = name.length() < maxNameLength ? name : name.substr(0, maxNameLength);

        maxNumChains = 2;
        coins = 0;

        istringstream defaultStringStream(defaultCString);
        hand = new Hand(defaultStringStream, CardFactory::getInstance());
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
    Chain<Card*>& operator[](int i) {
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
            out << *hand << endl;
        } else {
            out << hand->top() << endl;
        }
    }

    Hand& getHand() {
        return *hand;
    }

    friend ostream& operator<<(ostream& out, const Player& player);
};

int Player::maxNameLength = 10;

ostream& operator<<(ostream& out, const Player& player) {
    out << player.name << " " << player.coins << " coins " << player.maxNumChains << " chains" << endl;
    out << player.chains[0] << endl;
    out << player.chains[1] << endl;
    out << player.chains[2] << endl;
    return out;
}

#endif //BEANS_PLAYER_H
