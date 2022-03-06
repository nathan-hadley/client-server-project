#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

using namespace std;

class Connect4 {
public:
    Connect4();
    bool clientDrop(int dropChoice);
    void computerDrop();
    bool checkFour(bool client);

private:
    char board[7][6];
    string strBoard;

    void restart();
    bool fullBoard();
    void playerWin (bool client);
};

#endif //SERVER_CONNECT4_H
