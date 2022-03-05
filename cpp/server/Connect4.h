#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

using namespace std;

// TODO game logic
class Connect4 {
public:
    Connect4();
    bool clientDrop(int dropChoice);
    void computerDrop();
    int checkFour (string activePlayer);

private:
    char board[7][6];
    string strBoard;

    void restart();
    bool fullBoard();
    //void PlayerWin (playerInfo activePlayer);
};

#endif //SERVER_CONNECT4_H
