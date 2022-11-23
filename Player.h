//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_PLAYER_H
#define BEANS_PLAYER_H

#include <string>
#include <iostream>
#include <typeinfo>

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

    Chain<Card>* chains[3]{};
    Hand* hand;
public:

    Player() = default;

    /**
     * Constructor for creating a player from an istream
     * @param in
     * @param factory
     */
    Player(istream& in, CardFactory* factory) {
        string word;

        string line;
        istringstream *ss;

        int c = 0;

        // Line 1 (player info)
        getline(in, line);
        ss = new istringstream(line);
        while (*ss >> word) {
            switch(c) {
                case 0: // Get name
                    name = word;
                    break;
                case 1: // Get n coins
                    coins = stoi(word);
                    break;
                case 3:
                    maxNumChains = stoi(word);
            }

            c++;
        }

        // Line 2,3,4 (Chain 0,1,2)
        for (int i = 0; i < 3; i++) {
            delete ss;
            getline(in, line);
            ss = new istringstream(line);

            *ss >> word;

            if (word != "Card:") {
                // TODO: Parse word into card class
                chains[i] = new Chain<Card>(*ss, factory);
            }
        }

        // Line 5 (Hand)
        delete ss;
        getline(in, line);
        ss = new istringstream(line);
        *ss >> word;

        hand = new Hand(*ss, factory);
    }

    /**
     * Create player with name
     */
    explicit Player(string& name) {

        this->name = name;

        maxNumChains = 2;
        coins = 0;
        hand = new Hand();
    }

    Player(Player& o) {
        if (this != &o) {
            // Delete old pointers
            for (int i = 0; i < maxNumChains; i++) {
                delete chains[i];
            }
            delete hand;

            coins = o.coins;
            maxNumChains = o.maxNumChains;

            for (int i = 0; i < o.maxNumChains; i++) {
                chains[i] = o.chains[i];
            }
            hand = o.hand;
        }
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
    int getNumCoins() const {
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
    Chain<Card>& operator[](int i) {
        if (i < 0 || i >= maxNumChains) {
            throw out_of_range("Index is out of range!");
        }

        return *chains[i];
    }

    template <class T>
    void playOnChain(int idx, T* card) {

        if (idx < 0 || idx > maxNumChains) {
            throw out_of_range("Idx out of maxNumChains range");
        }

        // Create chain if null
        if (chains[idx] == nullptr) {
            chains[idx] = new Chain<T>();
        } else if (!chains[idx]->chainMatchesType(card)) {
            *this += chains[idx]->sell();
            delete chains[idx];
            chains[idx] = new Chain<T>();
        }

        *chains[idx] += card;
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
            out << *hand;
        } else if (hand->size() > 0) {
            out << hand->top()->getName() << endl;
        }
    }

    Hand& getHand() {
        return *hand;
    }

    void print(ostream& out, bool stubChains = false) const {
        out << name << " " << coins << " coins " << maxNumChains << " chains" << endl;
        for (int i = 0; i < (stubChains ? 3 : maxNumChains); i++) {

            if (chains[i] == nullptr) {
                out << "Card:" << endl;
            } else if (stubChains) {
                chains[i]->save(out);
            } else {
                out << *chains[i];
            }
        }
    }

    /**
     * Return a valid chain index chosen by player
     * @param out
     * @param in
     * @return
     */
    int selectChain(ostream& out, istream& in) {

        int chainIndex = 0;

        while (chainIndex < 1 || chainIndex > getMaxNumChains()) {
            out << "Select chain onto which to play your next card (1, 2";
            if (getMaxNumChains() == 3) {
                out << ", 3";
            }

            out << "): ";

            in.ignore();
            in >> chainIndex;
            out << endl;
        }

        return chainIndex - 1;
    }

    friend ostream& operator<<(ostream& out, const Player& player);
};

ostream& operator<<(ostream& out, const Player& player) {
    player.print(out, true);

    return out;
}

#endif //BEANS_PLAYER_H
