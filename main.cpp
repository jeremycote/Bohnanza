#include <iostream>
#include <sstream>
#include "Player.h"
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

    // Determine if we should resume an existing game
    /*
    bool resume;
    char resumeChar;
    cout << "Would you like to resume an existing game (yes/no): ";
    cin >> resumeChar;
    cout << endl;
    resume = resumeChar == 'y';
     */

    bool resume = true;

    Table* table;

    if (resume) {

        cout << "Enter savefile name: ";
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

            // Display table
            cout << *table;
            players[i]->printHand(cout, true);

            // Player draws top card from deck
            players[i]->getHand() += deck->draw();

            // If trade area is not empty
            if (tradeArea->numCards() > 0) {
                // TODO: Add beans to chains or discard them
            }

            int play = 0;
            while (play < 2) {
                // Play top card from hand
                cout << "Next card to play is: ";
                players[i]->printHand(cout, false);

                int chainIndex = 0;

                while (chainIndex < 1 || chainIndex > players[i]->getMaxNumChains()) {
                    cout << "Select chain onto which to play your next card (1, 2";
                    if (players[i]->getMaxNumChains() == 3) {
                        cout << ", 3";
                    }

                    cout << "): ";

                    cin >> chainIndex;
                    cout << endl;
                }

                // Decrement chain index to convert from human index to array index;
                chainIndex--;

                players[i]->playOnChain(chainIndex, players[i]->getHand().play());

                if (play == 0 && !askYesNo("Would you like to plant a second bean")){
                    play++;
                }
                play++;
            }

            players[i]->printHand(cout, true);

            if (askYesNo("Would you like to plant a second bean")) {

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
            for (int idx = 0; idx < 3; idx++) {
                *tradeArea += deck->draw();
            }

            // While top card of discard matches card in trade area
            while (tradeArea->legal(discard->top())) {
                // Draw card and place it in the trade area
                *tradeArea += discard->pickUp();
            }

            // for all cards in trade area
            for (int idx = 0; idx < tradeArea->numCards(); idx++) {
                // TODO: Get name of cards to trade
                tradeArea->trade("name");
            }

            // Draw two cards and add them to the player's hand
            for (int idx = 0; idx < 2; idx++) {
                players[i]->getHand() += deck->draw();
            }
        }
    }

    return 0;
}
