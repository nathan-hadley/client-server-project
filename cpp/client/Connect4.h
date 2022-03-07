#ifndef CLIENT_CONNECT4_CPP_H
#define CLIENT_CONNECT4_CPP_H

#include <string>
using namespace std;

class Connect4 {
public:
    static void displayBoard(const string& board);
    //static void displayBoard(char board[][10]);
    static string getColumnChoice();
    static bool gameOver(int gameStatus);
};

#endif //CLIENT_CONNECT4_CPP_H
