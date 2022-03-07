#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

using namespace std;

class Connect4 {
public:
    Connect4();
    bool clientDrop(int dropChoice);
    void computerDrop();
    bool fullBoard();
    bool checkFour(bool client);
    string boardToString();

private:
    char board[7][6];

    void restart();
    void playerWin (bool client);
};

#endif //SERVER_CONNECT4_H
