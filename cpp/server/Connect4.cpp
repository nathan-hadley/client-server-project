#include <string>
#include "Connect4.h"
using namespace std;

Connect4::Connect4() {
    restart();
}

void Connect4::restart() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = '*';
        }
    }
}

// assumes board is not full. Use fullBoard() to check.
// client always 'X'
bool Connect4::clientDrop(int dropChoice) {
    if (board[0][dropChoice] != '*') {
        int i = 0;
        while (board[i][dropChoice] != '*') {
            i++;
        }
        board[i][dropChoice] = 'X';
        return true;
    }
    return false;
}

// assumes board is not full. Use fullBoard() to check.
// computer always '0'
void Connect4::computerDrop() {
    srand(time(0));
    int dropChoice;

    do {
        dropChoice = rand() % 7;
    } while (board[0][dropChoice] != '*');

    int i = 0;
    while (board[i][dropChoice] != '*') {
        i++;
    }
    board[i][dropChoice] = 'X';
}

// Checks for full board.
bool Connect4::fullBoard() {
    int full = 0;
    for (int i = 0; i < 7; i++ ) {
        if (board[0][i] != '*' )
            full++;
    }
    if (full == 7)
        return true;
    else return false;
}


// Checks for four-in-a-row
bool Connect4::checkFour(bool client) {
    char XO;
    bool win = false;

    if (client)
        XO = 'X';
    else
        XO = '0';

    for (int i = 6; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {

            if (board[i][j] == XO && board[i-1][j-1] == XO &&
               board[i-2][j-2] == XO && board[i-3][j-3] == XO)
                win = true;

            if (board[i][j] == XO && board[i][j-1] == XO &&
               board[i][j-2] == XO && board[i][j-3] == XO)
                win = true;

            if (board[i][j] == XO && board[i-1][j] == XO &&
               board[i-2][j] == XO && board[i-3][j] == XO)
                win = true;

            if (board[i][j] == XO && board[i-1][j+1] == XO &&
               board[i-2][j+2] == XO && board[i-3][j+3] == XO)
                win = true;

            if (board[i][j] == XO && board[i][j+1] == XO &&
                board[i][j+2] == XO && board[i][j+3] == XO)
                win = true;
        }
    }
    return win;
}

void Connect4::playerWin(bool client) {
    if (client) {
        // do something
    } else {
        // do something else
    }
}

 

 
 
