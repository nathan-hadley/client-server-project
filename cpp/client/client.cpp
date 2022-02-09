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
using namespace std;

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

        cout << "\nEnter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

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
        if (response == 1)
            validLogin = true;
        else
            printf("Invalid username and/or password.\n");
    }

    // Obtain a random number from hardware
    random_device rd; 
    // Seed the generator
    mt19937 gen(rd());
    // Define the range 
    uniform_int_distribution<> distr(1, 10);

    int seconds = distr(gen);
    sleep(seconds);
    cout << "\nSlept for " << seconds << " seconds." << endl;

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