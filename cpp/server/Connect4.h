#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

using namespace std;

class Connect4 {
public:
    Connect4();
    string getBoardString();
    bool clientDrop(int dropChoice);
    int computerDrop();
    bool fullBoard();
    bool checkFour(bool client);

private:
    string* boardString;
    char board[6][7];

    void restart();
    void boardToString();
    void stringToBoard();
};

#endif //SERVER_CONNECT4_H
