#include <iostream>
#include <sstream>
#include "Player.h"
#include "Exceptions/DeckEmptyException.h"
#include "Structures/Deck.h"
#include "CardFactory.h"
#include "Structures/Table.h"
#include <string>
#include <fstream>

using namespace std;

const string Black::name = "Black";
const string Blue::name = "Blue";
const string Chili::name = "Chili";
const string Garden::name = "Garden";
const string Green::name = "Green";
const string Red::name = "Red";
const string Soy::name = "Soy";
const string Stink::name = "Stink";

int ChainBase::longestLabel = 6;
int ChainBase::spacer = 3;

CardFactory CardFactory::instance = CardFactory();

bool askYesNo(const string& question) {

    string answer = " ";

    while ((answer[0] != 'y' && answer[0] != 'n')) {
        cout << question << " (yes/no): ";
        getline(cin, answer);
        cout << endl;
    }
    return answer[0] == 'y';
}

int main() {

    Table* table;

    if (askYesNo("Would you like to resume an existing game?")) {
        cout << "Enter save file name: ";
        string filename;
        getline(cin, filename);

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
        table = new Table(CardFactory::getInstance());
    }

    Deck* deck = table->getDeck();
    TradeArea* tradeArea = table->getTradeArea();
    DiscardPile* discard = table->getDiscardPile();

    const int nPlayers = 2;

    // Game loop. Game ends when the deck is empty.
    while (!deck->empty()) {

        if (askYesNo("Would you like to save and quit")) {

            cout << "Enter filename: ";
            string filename;
            getline(cin, filename);
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

        // For each player
        for (int i = 0; i < nPlayers; i++) {

            cout << "It's " << table->getPlayer(i)->getName() << " turn!" << endl;

            // Display table
            cout << *table;
            table->getPlayer(i)->printHand(cout, true);

            // Ask player to buy a 3rd bean field if they can afford it and don't have one.
            if (table->getPlayer(i)->getMaxNumChains() == 2 && table->getPlayer(i)->getNumCoins() >= 3 && askYesNo("Would you like to purchase a third bean field?")) {
                table->getPlayer(i)->buyThirdChain();
                cout << *table;
            }

            // Player draws top card from deck
            try {
                Card* card = deck->draw();
                cout << table->getPlayer(i)->getName() << " drew a " << card->getName() << endl;
                table->getPlayer(i)->getHand() += card;
            } catch (DeckEmptyException& e) {
                cout << "Warning. Deck is empty" << endl;
            }


            // Display hand
            table->getPlayer(i)->printHand(cout, true);

            // If trade area is not empty
            if (tradeArea->numCards() > 0) {
                // Chain cards from the trade area
                if (askYesNo("Would you like to pick up cards from the trade area?")) {

                    bool continueTrading = true;

                    while (continueTrading) {
                        string cardNameToPickup;

                        cout << "Enter card name to pickup (Enter 'STOP' to stop trading): ";
                        getline(cin, cardNameToPickup);
                        cout << endl;

                        if (tradeArea->contains(cardNameToPickup)) {
                            table->getPlayer(i)->playOnChain(table->getPlayer(i)->selectChain(cout,cin), tradeArea->trade(cardNameToPickup));

                            // Display trade area
                            cout << *table;
                        } else if (cardNameToPickup == "STOP" || cardNameToPickup == "stop" || cardNameToPickup == "s" || cardNameToPickup == "S" || askYesNo("Trade area does not contain card, would you like to stop trading?")) {
                            continueTrading = false;
                        }
                    }
                }

                while (tradeArea->numCards() > 0) {
                    *discard += tradeArea->getCard();
                }
            }

            // Play up to 2 bean cards
            for (int play = 0; play < 2; play++) {

                if (table->getPlayer(i)->getHand().size() == 0) {
                    cout << "Skipping planting phase. Hand is empty." << endl;
                    break;
                }

                cout << "Next card to play is: ";
                table->getPlayer(i)->printHand(cout, false);

                if (play == 1 && table->getPlayer(i)->getHand().size() > 0) {
                    if (!askYesNo("Would you like to plant a second bean?")) {
                        // If they choose no, break out of for loop
                        break;
                    }
                }

                int chainIndex = table->getPlayer(i)->selectChain(cout, cin);
                table->getPlayer(i)->playOnChain(chainIndex, table->getPlayer(i)->getHand().play());
            }

            table->getPlayer(i)->printHand(cout, true);

            if (table->getPlayer(i)->getHand().size() == 0) {
                cout << "Skipping discard phase because hand is empty." << endl;
            } else if (askYesNo("Would you like to discard a card?")) {
                int idx = -1;
                while (idx < 0 || idx > table->getPlayer(i)->getHand().size()) {
                    cout << "Select card to discard (Enter '0' to cancel): ";
                    try {
                        string response;
                        getline(cin, response);
                        idx = stoi(response);
                    } catch (invalid_argument& e) {
                        cout << "Invalid choice." << endl;
                    }
                    cout << endl;
                }
                idx--;

                if (idx >= 0) {
                    *discard += table->getPlayer(i)->getHand()[idx];
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
            while (!discard->empty() && tradeArea->legal(discard->top())) {
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
                    getline(cin, cardNameToPickup);
                    cout << endl;

                    if (tradeArea->contains(cardNameToPickup)) {
                        table->getPlayer(i)->playOnChain(table->getPlayer(i)->selectChain(cout,cin), tradeArea->trade(cardNameToPickup));

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
                    table->getPlayer(i)->getHand() += deck->draw();
                }
            } catch (DeckEmptyException& e) {
                // Do nothing since cards are no longer used
            }
        }
    }

    int winner = -1;

    for (int i = 0; i < nPlayers; i++) {
        if (table->win(table->getPlayer(i)->getName())) {
            winner = i;
        }
    }

    if (winner == -1) {
        cout << "It's a tie! Both players have " << table->getPlayer(0)->getNumCoins() << " coins!" << endl;
    } else {
        cout << table->getPlayer(winner)->getName() << " wins!" << endl;
        for (int i = 0; i < nPlayers; i++) {
            cout << table->getPlayer(i)->getName() << " has " << table->getPlayer(i)->getNumCoins() << " coins." << endl;
        }
    }

    return 0;
}
