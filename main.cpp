#include <iostream>
#include <sstream>
#include "Player.h"
#include "Exceptions/DeckEmptyException.h"
#include "Structures/Deck.h"
#include "CardFactory.h"
#include "Structures/Table.h"
#include <string>
#include <fstream>
#include "Constants.h"

using namespace std;

CardFactory CardFactory::instance = CardFactory();

bool askYesNo(string question) {
    char playChar;
    cout << question << " (yes/no): ";
    cin >> playChar;
    cout << endl;

    return playChar == 'y';
}

int main() {

    Table* table;

    if (askYesNo("Would you like to resume an existing game?")) {
        cout << "Enter save file name: ";
        string filename;
        cin >> filename;

        ifstream file(filename, ifstream::in);

        if (!file) {
            cout << "Failed to load save file." << endl;
            return 1;
        }

        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);

        cout << "Save file contains " << length << " characters." << endl;

        table = new Table(file, CardFactory::getInstance());

        file.close();
    } else {
        table = new Table();
    }

    Deck* deck = table->getDeck();
    TradeArea* tradeArea = table->getTradeArea();
    DiscardPile* discard = table->getDiscardPile();

    const int nPlayers = 2;
    Player* players[nPlayers]{table->getPlayer(0), table->getPlayer(1)};

    // Game loop. Game ends when the deck is empty.
    while (!deck->empty()) {

        // For each player
        for (int i = 0; i < nPlayers; i++) {
            // Display table
            cout << *table;

            if (players[i]->getMaxNumChains() == 2 && players[i]->getNumCoins() >= 3 && askYesNo("Would you like to purchase a third bean field?")) {
                players[i]->buyThirdChain();
                cout << *table;
            }

            // Player draws top card from deck
            try {
                Card* card = deck->draw();
                cout << players[i]->getName() << " drew a " << card->getName() << endl;
                players[i]->getHand() += card;
            } catch (DeckEmptyException& e) {
                cout << "Warning. Deck is empty" << endl;
            }


            // Display hand
            players[i]->printHand(cout, true);

            // If trade area is not empty
            if (tradeArea->numCards() > 0) {
                // TODO: Add beans to chains or discard them
            }

            for (int play = 0; play < 2; play++) {

                if (players[i]->getHand().size() == 0) {
                    cout << "Skipping planting phase. Hand is empty." << endl;
                    break;
                }

                cout << "Next card to play is: ";
                players[i]->printHand(cout, false);

                if (play == 1 && players[i]->getHand().size() > 0) {
                    if (!askYesNo("Would you like to plant a second bean?")) {
                        // If they choose no, break out of for loop
                        break;
                    }
                }

                int chainIndex = players[i]->selectChain(cout, cin);
                players[i]->playOnChain(chainIndex, players[i]->getHand().play());
            }

            players[i]->printHand(cout, true);

            if (players[i]->getHand().size() == 0) {
                cout << "Skipping discard phase because hand is empty." << endl;
            } else if (askYesNo("Would you like to discard a card?")) {
                int idx = -1;
                while (idx < 0 || idx > players[i]->getHand().size()) {
                    cout << "Select card to discard (Enter '0' to cancel): ";
                    cin >> idx;
                    cout << endl;
                }
                idx--;

                if (i >= 0) {
                    *discard += players[i]->getHand()[idx];
                }
            }

            // Draw three cards and place them in the trade area;
            try {
                for (int idx = 0; idx < 3; idx++) {
                    *tradeArea += deck->draw();
                }
            } catch (DeckEmptyException& e) {
                cout << "Warning. Deck is empty. This is the last turn!" << endl;
            }


            // While top card of discard matches card in trade area
            while (tradeArea->legal(discard->top())) {
                // Draw card and place it in the trade area
                *tradeArea += discard->pickUp();
            }

            // Display trade area
            cout << *table;

            // Chain cards from the trade area
            if (askYesNo("Would you like to pick up cards from the trade area?")) {

                bool continueTrading = true;

                while (continueTrading) {
                    string cardNameToPickup;

                    cout << "Enter card name to pickup (Enter 'STOP' to stop trading): ";
                    cin >> cardNameToPickup;
                    cout << endl;

                    if (tradeArea->contains(cardNameToPickup)) {
                        players[i]->playOnChain(players[i]->selectChain(cout,cin), tradeArea->trade(cardNameToPickup));

                        // Display trade area
                        cout << *table;
                    } else if (cardNameToPickup == "STOP" || cardNameToPickup == "stop" || cardNameToPickup == "s" || cardNameToPickup == "S" || askYesNo("Trade area does not contain card, would you like to stop trading?")) {
                        continueTrading = false;
                    }
                }
            }

            // Draw two cards and add them to the player's hand

            try {
                for (int idx = 0; idx < 2; idx++) {
                    players[i]->getHand() += deck->draw();
                }
            } catch (DeckEmptyException& e) {
                // Do nothing since cards are no longer used
            }



            if (askYesNo("Would you like to save and quit")) {

                cout << "Enter filename: ";
                string filename;
                cin >> filename;
                cout << endl;

                ofstream file(filename, ifstream::out);

                if (file) {

                    cout << "Saving to: " << filename << endl;

                    table->saveTable(file);

                    file.close();

                    return 0;
                } else {
                    cout << "Failed to save file." << endl;
                }
            }
        }
    }

    int winner = -1;

    for (int i = 0; i < nPlayers; i++) {
        if (table->win(players[i]->getName())) {
            winner = i;
        }
    }

    if (winner == -1) {
        cout << "It's a tie! Both players have " << players[0]->getNumCoins() << " coins!" << endl;
    } else {
        cout << players[winner]->getName() << " wins!" << endl;
        for (auto & player : players) {
            cout << player->getName() << " has " << player->getNumCoins() << " coins." << endl;
        }
    }

    return 0;
}
