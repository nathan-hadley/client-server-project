#include <iostream>
using namespace std;

// TODO game logic client side

struct PlayerInfo {
    string playerName;
    char playerID;
};

class Connect4 {
    PlayerInfo activePlayer;

    /*int PlayerDrop() {
        int dropChoice;
        do {
            cout << activePlayer.playerName << "'s Turn ";
            cout << "Please enter a number between 1 and 7: ";
            cin >> dropChoice;

            while (board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O') {
                cout << "That row is full, please enter a new row: ";
                cin >> dropChoice;
            }

        } while (dropChoice < 1 || dropChoice > 7);

        return dropChoice;
    }*/

    public: void DisplayBoard (string board) {
        int rows = 6, columns = 7, i, ix;

        for (i = 1; i <= rows; i++) {
            cout << "|";
            cout << board.substr((i-1)*rows,columns);
            cout << "|" << endl;
        }
        cout << endl;
    }
};
