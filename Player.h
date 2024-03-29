//
// Created by Jeremy Cote on 2022-11-04.
//

#ifndef BEANS_PLAYER_H
#define BEANS_PLAYER_H

#include <string>
#include <iostream>
#include <typeinfo>

#include "Structures/Chain.h"
#include "Structures/Hand.h"

#include "Exceptions/NotEnoughCoinsException.h"

using namespace std;

/**
 * Represents a player, with name, coins, hand and chains
 */
class Player {
private:
    string name;
    int coins;
    int maxNumChains;

    ChainBase* chains[3]{};
    Hand* hand;

    /**
     * Private half of the playOnChain method.
     * @tparam T
     * @param idx
     * @param card
     */
    template<class T>
    void _playOnChain(int idx, Card* card) {
        // Create chain if null
        if (chains[idx] == nullptr) {
            chains[idx] = new Chain<T>();
        } else {
            // Cast existing chain to child type
            auto* pChain = dynamic_cast<Chain<T>*>(chains[idx]);

            // If cast failed, the chain contains cards of a different type. Sell it and make a new one.
            if (pChain == nullptr) {
                *this += chains[idx]->sell();
                delete chains[idx];
                chains[idx] = new Chain<T>();
            }
        }

        // Play card onto chain.
        auto* chain = dynamic_cast<Chain<T>*>(chains[idx]);
        *chain += card;
    }
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
            word.pop_back();

            // Parse first word of line as Chain type
            if (word != "Card") {
                if (word == Black::name) {
                    chains[i] = new Chain<Black>(*ss, factory);
                } else if (word == Blue::name) {
                    chains[i] = new Chain<Blue>(*ss, factory);
                } else if (word == Chili::name) {
                    chains[i] = new Chain<Chili>(*ss, factory);
                } else if (word == Garden::name) {
                    chains[i] = new Chain<Garden>(*ss, factory);
                } else if (word == Red::name) {
                    chains[i] = new Chain<Red>(*ss, factory);
                } else if (word == Soy::name) {
                    chains[i] = new Chain<Soy>(*ss, factory);
                } else if (word == Stink::name) {
                    chains[i] = new Chain<Stink>(*ss, factory);
                }
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

    /*
     *  Copy Constructor for player.
     *  Delete old chains and copy pointers pointing to new chains
     */
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
     * Get number of chains that aren't empty.
     * @return
     */
    int getNumChains() const {
        int c = 0;
        for (int i = 0; i < maxNumChains; i++) {
            if (chains[i] != nullptr) {
                c++;
            }
        }

        return c;
    }

    /**
     * Add coins to player's total
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
    int getMaxNumChains() const {
        return maxNumChains;
    }

    /**
     * Return Chain at position i
     * @param i
     * @return
     */
    ChainBase& operator[](int i) {
        if (i < 0 || i >= maxNumChains) {
            throw out_of_range("Index is out of range!");
        }

        return *chains[i];
    }

    /**
     * Add a card onto a chain with idx.
     * @param idx
     * @param card
     */
    void playOnChain(int idx, Card* card) {

        if (idx < 0 || idx > maxNumChains) {
            throw out_of_range("Idx out of maxNumChains range");
        }

        // Find type of card and call appropriate private playOnChain function.

        auto* black = dynamic_cast<Black*>(card);
        if (black != nullptr) {
            _playOnChain<Black>(idx, card);
            return;
        }

        auto* blue = dynamic_cast<Blue*>(card);
        if (blue != nullptr) {
            _playOnChain<Blue>(idx, card);
            return;
        }

        auto* chili = dynamic_cast<Chili*>(card);
        if (chili != nullptr) {
            _playOnChain<Chili>(idx, card);
            return;
        }

        auto* garden = dynamic_cast<Garden*>(card);
        if (garden != nullptr) {
            _playOnChain<Garden>(idx, card);
            return;
        }

        auto* green = dynamic_cast<Green*>(card);
        if (green != nullptr) {
            _playOnChain<Green>(idx, card);
            return;
        }

        auto* red = dynamic_cast<Red*>(card);
        if (red != nullptr) {
            _playOnChain<Red>(idx, card);
            return;
        }

        auto* soy = dynamic_cast<Soy*>(card);
        if (soy != nullptr) {
            _playOnChain<Soy>(idx, card);
            return;
        }

        auto* stink = dynamic_cast<Stink*>(card);
        if (stink != nullptr) {
            _playOnChain<Stink>(idx, card);
            return;
        }

        throw IllegalTypeException();
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

    /**
     * Print hand into ostream.
     * @param out
     * @param entireHand should print the entire hand or just the next card to be played.
     */
    void printHand(ostream& out, bool entireHand) {
        if (entireHand) {
            out << *hand;
        } else if (hand->size() > 0) {
            out << hand->top()->getName() << endl;
        }
    }

    /**
     * Return reference to player's hand.
     * @return
     */
    Hand& getHand() {
        return *hand;
    }

    /**
     * Write player into ostream.
     * Stub chains will create empty rows for empty chains.
     * @param out
     * @param stubChains
     */
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

            try {
                string response;
                getline(in, response);
                chainIndex = stoi(response);
            } catch (invalid_argument& e) {
                out << "Invalid choice." << endl;
            }
            out << endl;
        }

        return chainIndex - 1;
    }

    /**
     * Write player into ostream without stubbing.
     * @param out
     * @param player
     * @return
     */
    friend ostream& operator<<(ostream& out, const Player& player);
};

ostream& operator<<(ostream& out, const Player& player) {
    player.print(out, true);

    return out;
}

#endif //BEANS_PLAYER_H
