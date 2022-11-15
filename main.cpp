#include <iostream>
#include <sstream>
#include "Player.h"
#include "Structures/Deck.h"
#include "CardFactory.h"
#include "Structures/Table.h"
#include <string>
#include "Constants.h"

using namespace std;

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

    bool resume = false;

    // TODO: Initialize structures properly

    Deck deck;
    Table table;
    TradeArea tradeArea;
    DiscardPile discard;

    const int nPlayers = 2;
    Player players[nPlayers]{Player(), Player()};


    if (resume) {
        // Resume a game by using istream constructors
        players[0] = Player(cin, CardFactory::getInstance());
        players[1] = Player(cin, CardFactory::getInstance());
        deck = Deck(cin, CardFactory::getInstance());
        discard = DiscardPile(cin, CardFactory::getInstance());
        tradeArea = TradeArea(cin, CardFactory::getInstance());
        table = Table(cin, CardFactory::getInstance(), &players[0], &players[1], &deck, &discard, &tradeArea);
    } else {

        string p1Name;
        string p2Name;

        cout << "Enter P1 Name: ";
        cin >> p1Name;
        cout << endl << "Enter P2 Name: ";
        cin >> p2Name;
        cout << endl;

        players[0] = Player(p1Name);
        players[1] = Player(p2Name);

        // Start a new game by using default constructors
        deck = CardFactory::getInstance()->getDeck();
        table = Table(&players[0], &players[1], &deck, &discard, &tradeArea);
    }

    // Game loop. Game ends when the deck is empty.
    while (!deck.empty()) {

        // TODO: Ask to pause game
        if (false) {
            cout << players[0];
            cout << players[1];
            cout << deck;
            cout << discard;
            cout << tradeArea;
            cout << table;
        }

        // For each player
        for (int i = 0; i < nPlayers; i++) {
            // Display table
            cout << table;

            // Player draws top card from deck
            players[i].getHand() += deck.draw();

            // If trade area is not empty
            if (tradeArea.numCards() > 0) {
                // TODO: Add beans to chains or discard them
            }

            int play = 0;
            while (play < 2) {
                // Play top card from hand
                cout << "Next card to play is: ";
                players[i].printHand(cout, false);

                // TODO: get index of chain to play on
                players[i][0] += players[i].getHand().play();

                play++;

                // TODO: ask user if they want to play a second card
                if (true) {
                    play = 2;
                }
            }

            // TODO: ask to display hand and discard
            players[i].printHand(cout, true);
            // TODO: get index of card to discard
            discard += players[i].getHand()[0];

            // Draw three cards and place them in the trade area;
            for (int idx = 0; idx < 3; idx++) {
                tradeArea += deck.draw();
            }

            // While top card of discard matches card in trade area
            while (tradeArea.legal(discard.top())) {
                // Draw card and place it in the trade area
                tradeArea += discard.pickUp();
            }

            // for all cards in trade area
            for (int idx = 0; idx < tradeArea.numCards(); idx++) {
                // TODO: Get name of cards to trade
                tradeArea.trade("name");
            }

            // Draw two cards and add them to the player's hand
            for (int idx = 0; idx < 2; idx++) {
                players[i].getHand() += deck.draw();
            }
        }
    }

    return 0;
}
