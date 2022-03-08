#ifndef SERVER_CONNECT4_H
#define SERVER_CONNECT4_H

using namespace std;

class Connect4 {
public:
    Connect4();
    void restart();
    string getBoardString();
    bool clientDrop(int dropChoice);
    int computerDrop();
    bool fullBoard();
    bool checkFour(bool client);

private:
    string boardString;
    char board[6][7]{};

    string boardToString();
    //void boardToString();
    void stringToBoard();
};

#endif //SERVER_CONNECT4_H
