#include <string>
#include <iostream>
#include "Connect4.h"
using namespace std;

// TODO make game logic work

Connect4::Connect4() {
    restart();
}

void Connect4::restart() {
    for (int i = 1; i <= 6; i++) {
        for (int ix = 1; ix <= 7; ix++) {
            board[i][ix] = '*';
        }
    }
}

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


/*
int Connect4::CheckFour ( char board[][10], playerInfo activePlayer )
{
    char XO;
    int win;

    XO = activePlayer.playerID;
    win = 0;

    for( int i = 8; i >= 1; --i )
    {

        for( int ix = 9; ix >= 1; --ix )
        {

            if( board[i][ix] == XO     &&
                board[i-1][ix-1] == XO &&
                board[i-2][ix-2] == XO &&
                board[i-3][ix-3] == XO )
            {
                win = 1;
            }


            if( board[i][ix] == XO   &&
                board[i][ix-1] == XO &&
                board[i][ix-2] == XO &&
                board[i][ix-3] == XO )
            {
                win = 1;
            }

            if( board[i][ix] == XO   &&
                board[i-1][ix] == XO &&
                board[i-2][ix] == XO &&
                board[i-3][ix] == XO )
            {
                win = 1;
            }

            if( board[i][ix] == XO     &&
                board[i-1][ix+1] == XO &&
                board[i-2][ix+2] == XO &&
                board[i-3][ix+3] == XO )
            {
                win = 1;
            }

            if ( board[i][ix] == XO   &&
                 board[i][ix+1] == XO &&
                 board[i][ix+2] == XO &&
                 board[i][ix+3] == XO )
            {
                win = 1;
            }
        }

    }

    return win;
}

void Connect4::PlayerWin ( playerInfo activePlayer )
{
    cout << endl << activePlayer.playerName << " Connected Four, You Win!" << endl;
}

 */
 

 
 
