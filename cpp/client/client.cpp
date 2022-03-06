// Client side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iterator>
#include <iostream>
#include <random>
#include "Connect4.h"
using namespace std;

bool ConnectToServer(const char* serverAddress, int port, int& sock);
void sendRPC(const string& RPC, const int& sock, vector<string>& arrayTokens);
void ParseTokens(char* buffer, vector<string>& a);

int main(int argc, char const* argv[]) {
    // Takes first command line argument: IP address of the server
    const char* serverAddress = argv[1];
    // Takes second command line argument: port the server is listening on
    const int port = atoi(argv[2]);

    int sock = 0;
    vector<string> arrayTokens;

    bool bConnect = ConnectToServer(serverAddress, port, sock);

    bool validLogin = false;
    while (bConnect && !validLogin) {
        string username,
        password,
        connectRPC;

        // Collect username and password
        cout << "\nEnter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        // Create string to send to server. Ex.: connect;USERNAME;PASSWORD1234;"
        connectRPC.append("connect;").append(username).append(";");
        connectRPC.append(password).append(";");

        sendRPC(connectRPC, sock, arrayTokens);

        // Authenticate login
        if (stoi(arrayTokens[0]) == 1) {
            validLogin = true;
            printf("Login successful.\n");
            cout << "Welcome to Connect Four!" << endl;
        } else
            printf("Invalid username and/or password.\n");
    }

    // PlayConnect4RPC Section
    // Needs to be cleaned up and have ability for player to choose if computer
    // or player takes first turn
    bool continuePlaying = true;
    while (continuePlaying && bConnect) {
        auto* game = new Connect4();

        string turnChoice = "";
        while (turnChoice != "1" && turnChoice != "2") {
            cout << "To start a new game, enter \"1\" to take the first turn, "
                    "or enter \"2\" for the computer to take the first turn: ";
            cin >> turnChoice;
        }

        // Create string to send to server. Ex.: playconnectfour;"
        string playConnect4RPC;
        playConnect4RPC.append("playconnect4;").append(turnChoice);

        sendRPC(playConnect4RPC, sock, arrayTokens);

        // PlayPieceRPC Section
        // gameStatus will be what is returned from the server after the RPC
        // call. I think the following might make sense:
        // 1-7: The computer's column choice returned from the RPC call
        // 8: Player has selected a column that is full
        // 9: Player has won
        // 10: Computer has won
        int gameStatus;
        do {
            game->displayBoard(arrayTokens[0]);
            string columnChoice = game->getColumnChoice();

            // Create string to send to server.
            string playPieceRPC;
            playPieceRPC.append("playpiece;").append(columnChoice).append(";");

            sendRPC(playPieceRPC, sock, arrayTokens);

            gameStatus = stoi(arrayTokens[1]);

            if (gameStatus == 8)
                printf("You selected a column that is full. Please try again");
            else if (gameStatus >= 1 && gameStatus <= 8) {
                cout << "The computer has selected column " << gameStatus << "." << endl;
            }

        } while (gameStatus >= 1 && gameStatus <= 8);

        game->displayBoard(arrayTokens[0]);

        continuePlaying = game->gameOver(gameStatus);

    }

    // checkStatsRPC section
    // currently it displays the total games from all clients
    // still need work to display the total games by that particular client
    int gamesPlayed;
    string checkStatsRPC;
    checkStatsRPC.append("checkstats;");
    sendRPC(checkStatsRPC, sock, arrayTokens);
    gamesPlayed = stoi(arrayTokens[0]);
    cout << "Total number games played: " << gamesPlayed << endl;

    // Do a disconnect Message
    if (bConnect) {
        
        string exit;
        while (exit != "EXIT") {
            cout << "Type 'EXIT' to disconnect" << endl;
            cin >> exit;
        }

        const char* disconnectRPC = "disconnect;";
        sendRPC(disconnectRPC, sock, arrayTokens);

    } else {
        printf("Exit without calling RPC");
    }

    // Terminate connection
    close(sock);

    return 0;
}

/*
 * ConnectToServer will connect to the Server based on command line
 *
 * Input:
 *      serverAddress: The IP address of the server.
 *      port: The port the server is listening on.
 *      sock (passed by reference): A variable that will be assigned the socket.
 * Output:
 *      Returns true if a connection to the server is successful, false otherwise.
*/
bool ConnectToServer(const char* serverAddress, int port, int& sock) {
    struct sockaddr_in serv_addr{};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return false;
    }

    return true;
}

/*
 * Sends RPC to server.
 *
 * Input:
 *      RPC: string RPC.
 *      sock: socket to send message on.
 *      arrayTokens (passed by reference): token array to write buffer to.
 */
void sendRPC(const string& RPC, const int& sock, vector<string>& arrayTokens) {
    // Array of characters created as buffer, which will be passed to server
    char buffer[1024] = { 0 };
    int nlen;

    // Copies the characters from connectRPC to the buffer array
    strcpy(buffer, RPC.c_str());
    nlen = (int) strlen(buffer);
    // Puts the null terminator at the end of the connectRPC characters
    buffer[nlen] = 0;

    // Sends the contents of the buffer through the created socket
    send(sock, buffer, strlen(buffer) + 1, 0);

    // Assigns the server response to the buffer
    read(sock, buffer, 1024);

    arrayTokens.clear();
    ParseTokens(buffer, arrayTokens);
}

/*
 * ParseTokens splits a string by semicolons and adds all strings to the input
 * vector.
 *
 * Input:
 *      buffer: The string to be split
 *      a: The vector to have strings added to
 */
void ParseTokens(char* buffer, vector<string>& a) {
    char* token;
    char* rest = (char*)buffer;

    while ((token = strtok_r(rest, ";", &rest))) {
        a.emplace_back(token);
    }
}