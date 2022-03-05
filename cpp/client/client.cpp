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
#include "Connect4.cpp"
using namespace std;

bool ConnectToServer(const char* serverAddress, int port, int& sock);
string convertToString (char* a, int size);

int main(int argc, char const* argv[]) {
    int sock = 0;
    // Array of characters created as buffer, which will be passed to server?
    char buffer[1024] = { 0 };
    bool validLogin = false;

    // Takes first command line argument: IP address of the server
    const char* serverAddress = argv[1];
    // Takes second command line argument: port the server is listening on
    const int port = atoi(argv[2]);

    bool bConnect = ConnectToServer(serverAddress, port, sock);

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

        // Copies the characters from connectRPC to the buffer array
        strcpy(buffer, connectRPC.c_str());
        int nlen = (int) strlen(buffer);
        // Puts the null terminator at the end of the connectRPC characters
        buffer[nlen] = 0;

        // Sends the contents of the buffer through the created socket
        int valwrite = (int) send(sock, buffer, strlen(buffer) + 1, 0);

        printf("Connect message sent with %d bytes\n", valwrite);

        // Assigns the server response to the buffer
        int valread = (int) read(sock, buffer, 1024);
        printf("Return response = %s with valread = %d\n", buffer, valread);

        // Authenticate login
        int response = atoi(buffer);
        if (response == 1) {
            validLogin = true;
            printf("Login successful.\n");
        } else
            printf("Invalid username and/or password.\n");
    }

    cout << "Welcome to Connect Four!" << endl;

    /*
     * PlayPieceRPC Section
     * gameStatus will be what is returned from the server after the RPC call. I think the following might make sense:
     * Between 1 and 7: The computer's column choice returned from the RPC call
     * 8: Player has selected a column that is full
     * 9: Player has won
     * 10: Computer has won
     * */
    bool continuePlaying = true;
    bool newGame = true;
    int gameStatus = 1;
    Connect4* game = new Connect4();
    string board;
    int nlen, valwrite, valread;
    while (continuePlaying) {
        /*
                 * PlayConnect4RPC Section
                 * Needs to be cleaned up and have ability for player to choose if computer or player takes first turn
                 *
                 * */
        string playConnect4RPC;
        string turnChoice = "";
        while (turnChoice != "1" && turnChoice != "2") {
            cout << "To start a new game, enter \"1\" to take the first turn, or enter \"2\" for the computer to take the first turn: ";
            cin >> turnChoice;
        }

        // Create string to send to server. Ex.: playconnectfour;"
        playConnect4RPC.append("playconnect4;").append(turnChoice);

        // Copies the characters from connectRPC to the buffer array
        strcpy(buffer, playConnect4RPC.c_str());
        nlen = (int) strlen(buffer);
        // Puts the null terminator at the end of the connectRPC characters
        buffer[nlen] = 0;

        // Sends the contents of the buffer through the created socket
        valwrite = (int) send(sock, buffer, strlen(buffer) + 1, 0);

        printf("playconnect4 message sent with %d bytes\n", valwrite);

        // Assigns the server response to the buffer
        valread = (int) read(sock, buffer, 1024);

        int bLen = strlen(buffer);
        board = convertToString(buffer, bLen);
        printf("Return response = %s with valread = %d\n", buffer, valread);

        while (gameStatus >= 1 && gameStatus <= 8) {
            game->DisplayBoard(board);
            string columnChoice = "";
            string playPieceRPC;

            while (columnChoice != "1"  && columnChoice != "2"  && columnChoice != "3"
                && columnChoice != "4"  && columnChoice != "5"  && columnChoice != "6"  && columnChoice != "7") {
                cout << "Please enter which column you'd like to play your piece (must be between 1 and 7): ";
                cin >> columnChoice;
            }

            // Create string to send to server. Ex.: playpiece;"
            playPieceRPC.append("playpiece;").append(columnChoice);

            // Copies the characters from playpieceRPC to the buffer array
            strcpy(buffer, playPieceRPC.c_str());
            nlen = (int) strlen(buffer);
            // Puts the null terminator at the end of the connectRPC characters
            buffer[nlen] = 0;

            // Sends the contents of the buffer through the created socket
            valwrite = (int) send(sock, buffer, strlen(buffer) + 1, 0);

            printf("playconnect4 message sent with %d bytes\n", valwrite);

            // Assigns the server response to the buffer
            valread = (int) read(sock, buffer, 1024);

            string serverResponse(buffer);
            gameStatus = stoi(serverResponse);
            printf("Return response = %i with valread = %d\n", gameStatus, valread);
        }

        game->DisplayBoard(board);

        string input;
        if (gameStatus == 8) {
            cout << "You selected a column that is full. Please try again" << endl;
            continue;
        } else if (gameStatus == 9) {
            cout << "You win! Enter \"y\" to play again. Enter anything else to exit."  << endl;
            cin >> input;
            if (input == "y") {
                gameStatus = 1;
                continue;
            } else {
                continuePlaying = false;
            }
        } else if (gameStatus == 10) {
            cout << "The computer has won! Enter \"y\" to play again. Enter anything else to exit." << endl;
            cin >> input;
            if (input == "y") {
                gameStatus = 1;
                continue;
            } else {
                continuePlaying = false;
            }
        } else if (gameStatus == 11) {
            cout << "The game board is full! Enter \"y\" to play again. Enter anything else to exit." << endl;
            cin >> input;
            if (input == "y") {
                gameStatus = 1;
                continue;
            } else {
                continuePlaying = false;
            }
        } else {
            cout << "There was an error in the game. Enter \"y\" to play again. Enter anything else to exit." << endl;
            cin >> input;
            if (input == "y") {
                gameStatus = 1;
                continue;
            } else {
                continuePlaying = false;
            }
        }
    }

    // Do a disconnect Message
    if (bConnect) {
        
        string exit;
        const char* disconnectRPC = "disconnect;";
        
        while (exit != "EXIT") {
            cout << "Type 'EXIT' to disconnect" << endl;
            cin >> exit;
        }            

        // Copies the contents of the logoffRPC to the buffer
        strcpy(buffer, disconnectRPC);
        int nlen = (int) strlen(buffer);

        // Put null terminator at the end of the logoffRPC characters in the buffer
        buffer[nlen] = 0;

        // Sends the contents of the buffer through the created socket
        int valwrite = (int) send(sock, buffer, strlen(buffer) + 1, 0);

        printf("Disconnect message sent with %d bytes\n", valwrite);

        // Assign the server response to the buffer
        int valread = (int) read(sock, buffer, 1024);
        printf("Return response = %s with valread = %d\n", buffer, valread);

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
 *      serverAddress: The IP address of the server
 *      port: The port the server is listening on
 *      sock (passed by reference): A variable that will be assigned the socket
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
 * Converts an array of character to a string
*/
string convertToString (char* a, int size) {
    string s = "";

    for (int i = 0; i < size; i++) {
        s = s + a[i];
    }

    return s;
}