#include <iostream>
#include "Player.h"
#include "Structures/Deck.h"
#include "CardFactory.h"
#include <string>

using namespace std;

int main() {

    int startingHandSize = 5;

    // Determine if we should resume an existing game
    bool resume;
    char resumeChar;
    cout << "Would you like to resume an existing game (yes/no): ";
    cin >> resumeChar;
    cout << endl;
    resume = resumeChar == 'y';

    Deck* deck;

    Player* p1;
    Player* p2;

    if (resume) {

    } else {
        string p1Name;
        string p2Name;

        cout << "Enter P1 Name: ";
        cin >> p1Name;
        cout << endl << "Enter P2 Name: ";
        cin >> p2Name;
        cout << endl;

        p1 = new Player(p1Name);
        p2 = new Player(p2Name);

        deck = new Deck();
        *deck = CardFactory::getInstance()->getDeck();

        for (int i = 0; i < startingHandSize; i++) {
            p1->getHand() += deck->draw();
            p2->getHand() += deck->draw();
        }
    }

    // Game loop. Game ends when the deck is empty.
    while (!deck->empty()) {
        break;
    }

    return 0;
}
