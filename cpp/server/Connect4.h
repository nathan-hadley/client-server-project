#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

// TODO game logic
class Connect4 {
public:
    Connect4();
    //int PlayerDrop(playerInfo activePlayer );*/

private:
    char board[9][10];
    int trueWidth;
    int trueLength;
    void CheckBellow (int dropChoice, char playerToken);
    void restart ();
/*
    int CheckFour (char board[][10], playerInfo activePlayer);
    void PlayerWin (playerInfo activePlayer);
    int ComputerDrop(char board[][10]);
    int FullBoard(char board[][10] );*/
};

#endif //SERVER_CONNECT4_H
