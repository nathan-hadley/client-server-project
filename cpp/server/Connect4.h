#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

// TODO game logic
class Connect4 {
public:
    Connect4();
    int PlayerDrop(char board[][10], playerInfo activePlayer );

private:
    struct playerInfo;
    void CheckBellow (char board[][10], playerInfo activePlayer, int dropChoice);
    void DisplayBoard (char board[][10]);
    int CheckFour (char board[][10], playerInfo activePlayer);


    int restart (char board[][10]);

    void PlayerWin (playerInfo activePlayer);
    int ComputerDrop(char board[][10]);
    int FullBoard(char board[][10] );
};


#endif //SERVER_CONNECT4_H
