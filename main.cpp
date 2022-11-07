#include <iostream>
#include "Player.h"
#include <string>

using namespace std;

int main() {

    // Determine if we should resume an existing game
    bool resume;
    char resumeChar;
    cout << "Would you like to resume an existing game (yes/no): ";
    cin >> resumeChar;
    cout << endl;
    resume = resumeChar == 'y';

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

        cout << p1->getName() << endl;
        cout << p2->getName() << endl;
    }

    return 0;
}
