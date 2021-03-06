#include <string>
#include <sstream>
#include <iostream>
#include "Connect4.h"
using namespace std;

/**
 * Constructor.
 */
Connect4::Connect4() {
    restart();
}

string Connect4::getBoardString() {
    return boardToString();
}

/**
 * Clears board.
 */
void Connect4::restart() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = '*';
        }
    }
}

/**
 * Drops client piece onto board. Assumes board is not full. Use fullBoard() to
 * check. Client is always 'X'.
 * @param dropChoice: chosen column.
 * @return true if drop successful, false if column is full.
 */
bool Connect4::clientDrop(int dropChoice) {

    stringToBoard();
    if (board[5][dropChoice] == '*') {
        // Start at bottom of column and check for first empty slot
        int i = 5;
        while (board[i][dropChoice] != '*') {
            i--;
        }
        board[i][dropChoice] = 'X';
        boardToString();
        return true;
    }
    return false;
}

/**
 * Drops computer piece. Chooses a random column and assumes board is not full.
 * Use fullBoard() to check. Computer is always 'O'.
 * @return column choice.
 */
int Connect4::computerDrop() {
    srand(time(0));
    int dropChoice;

    // Get most up-to-date board.
    stringToBoard();
    // This loops seems to run forever when debugging
    do {
        dropChoice = rand() % 7;
    } while (board[0][dropChoice] != '*');

    int i = 5;
    while (board[i][dropChoice] != '*') {
        i--;
    }
    board[i][dropChoice] = 'O';
    // Convert board back to string.
    boardToString();

    return dropChoice + 1;
}

/**
 * Checks for full board.
 * @return true if full, false otherwise.
 */
bool Connect4::fullBoard() {
    int full = 0;
    for (int i = 0; i <= 6; i++) {
        if (board[0][i] != '*' )
            full++;
    }
    if (full == 7)
        return true;
    else return false;
}

string Connect4::boardToString() {
    //string result;
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 7; j++) {
             boardString += board[i][j];
        }
    }
    return boardString;
}

//void Connect4::boardToString() {
//    stringstream ss;
//    for (int i = 0; i <= 6; i++) {
//        for (int j = 0; j <= 7; j++) {
//            ss << to_string(board[i][j]);
//        }
//    }
//    *boardString = ss.str();
//}

void Connect4::stringToBoard() {
    for (int i = 0; i <= 6; i++)
    {
        for(int j = 0; j <= 7; j++)
        {
            board[i][j] = boardString[j + (i * 7)];
        }
    }

}
//void Connect4::stringToBoard() {
//    int count = 0;
//    for (int i = 0; i <= 6; i++) {
//        for (int j = 0; j <= 7; j++) {
//            board[i][j] = boardString.at(count);
//            count++;
//        }
//    }
//}

/**
 * Checks for four-in-a-row.
 * @param client: true if checking for client, false if checking for computer.
 * @return true if winner found.
 */
bool Connect4::checkFour(bool client) {
    char XO;
    bool win = false;

    if (client)
        XO = 'X';
    else
        XO = 'O';

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

 

 
 
