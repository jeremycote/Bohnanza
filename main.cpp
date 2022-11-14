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

    Table* table;

    if (resume) {

    } else {

        istringstream defaultStringStream(defaultCString);

        table = new Table(cin, CardFactory::getInstance());
    }

    // Game loop. Game ends when the deck is empty.
    while (!deck->empty()) {

        // P1
        cout << *table;
        break;
    }

    return 0;
}
