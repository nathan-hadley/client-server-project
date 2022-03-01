#include <string>
#include <iostream>
#include "Connect4.h"
using namespace std;

struct Connect4::playerInfo {
    string playerName;
    char playerID;
};


// TODO make game logic work

// Moved the commented out code below to client side.
/*
int Connect4::PlayerDrop(char board[][10], int activePlayer) {
    int dropChoice;
    do {
        cout << activePlayer.playerName << "'s Turn ";
        cout << "Please enter a number between 1 and 7: ";
        cin  >> dropChoice;

        while ( board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O' )
        {
            cout << "That row is full, please enter a new row: ";
            cin  >> dropChoice;
        }

    }while ( dropChoice < 1 || dropChoice > 7 );

    return dropChoice;
}*/

int Connect4::ComputerDrop( char board[][10])
{
    srand(time(0));
    int dropChoice = rand() % 7;

    while ( board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O' )
    {
        dropChoice = rand() % 7;
    }

    cout << "Computer has chosen row " << dropChoice << "." << endl << endl;

    return dropChoice;
}

void Connect4::CheckBellow ( char board[][10], playerInfo activePlayer, int dropChoice )
{
    int length, turn;
    length = 6;
    turn = 0;

    do
    {
        if ( board[length][dropChoice] != 'X' && board[length][dropChoice] != 'O' )
        {
            board[length][dropChoice] = activePlayer.playerID;
            turn = 1;
        }
        else
            --length;
    }while (  turn != 1 );


}

void Connect4::DisplayBoard ( char board[][10] )
{
    int rows = 6, columns = 7, i, ix;

    for(i = 1; i <= rows; i++)
    {
        cout << "|";
        for(ix = 1; ix <= columns; ix++)
        {
            if(board[i][ix] != 'X' && board[i][ix] != 'O')
                board[i][ix] = '*';

            cout << board[i][ix];

        }

        cout << "|" << endl;
    }

    cout << endl;
}

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

int Connect4::FullBoard( char board[][10] )
{
    int full;
    full = 0;
    for ( int i = 1; i <= 7; ++i )
    {
        if ( board[1][i] != '*' )
            ++full;
    }

    return full;
}

void Connect4::PlayerWin ( playerInfo activePlayer )
{
    cout << endl << activePlayer.playerName << " Connected Four, You Win!" << endl;
}

int Connect4::restart ( char board[][10] )
{
    int restart;

    cout << "Would you like to restart? Yes(1) No(2): ";
    cin  >> restart;
    if ( restart == 1 )
    {
        for(int i = 1; i <= 6; i++)
        {
            for(int ix = 1; ix <= 7; ix++)
            {
                board[i][ix] = '*';
            }
        }
    }
    else
        cout << "Goodbye!" << endl;
    return restart;
}