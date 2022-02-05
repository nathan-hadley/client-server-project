// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <iostream>

// This is a C Program. No classes. You may turn this into an Object Oriented C++ program if you wish

/*
    ParseTokens splits a string deliminates by semi-colons and adds all strings to the input vector
    Input:
            buffer: The string to be split
            a: The vector to have strings added to
*/
void ParseTokens(char* buffer, std::vector<std::string>& a)
{
    char* token;
    char* rest = (char*)buffer;

    while ((token = strtok_r(rest, ";", &rest)))
    {
        printf("%s\n", token);
        a.push_back(token);
    }

    return;
}

/*
    ConnectToServer will connect to the Server based on command line
    Input:
            serverAddress: The IP address of the server
            port: The port the server is listening on
            sock (passed by reference): A variable that will be assigned the socket
    Output:
            Returns true if a connection to the server is succesful, false otherwise.
*/
bool ConnectToServer(const char* serverAddress, int port, int& sock)
{
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return false;
    }

    return true;
}

int main(int argc, char const* argv[])
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    //const char* connectRPC = "connect;MIKE;MIKE;"; // Initial contents for connect RPC
    const char* statusRPC = "status;"; // Initial contents for status RPC
    const char* logoffRPC = "disconnect;"; // Initial contents for disconnect RPC
    char buffer[1024] = { 0 }; // Array of characters created as buffer, which will be passed to server?
    const char* serverAddress = argv[1]; // Takes first command line argument, which should be the IP address of the server
    const int port = atoi(argv[2]); // Takes second command line argument, which should be the port the server is listening on

    


    bool bConnect = ConnectToServer(serverAddress, port, sock);

    if (bConnect == true)
    {
        std::string username;
        std::cout << "Enter your username: ";
        std::cin >> username;

        std::string password;
        std::cout << "Enter your password: ";
        std::cin >> password;

        std::string connectRPC = "connect;" + username + ";" + password + ";";

        strcpy(buffer, connectRPC.c_str()); // Copies the characters from connectRPC to the buffer array
        int nlen = strlen(buffer); 
        buffer[nlen] = 0;   // Puts the null terminator at the end of the connectRPC characters

       int valwrite = send(sock, buffer, strlen(buffer) + 1, 0); // Sends the contents of the buffer through the created socket

        printf("Connect message sent with %d bytes\n", valwrite);

        int valread = read(sock, buffer, 1024); // Assigns the server response to the buffer
        printf("Return response = %s with valread = %d\n", buffer, valread);



    }
    else
    {
        printf("Exit without calling RPC");
    }


    // Do a Disconnect Message

    if (bConnect == true)
    {
        strcpy(buffer, logoffRPC); // Copies the contents of the logoffRPC to the buffer
        int nlen = strlen(buffer);
        buffer[nlen] = 0;   // Puts the null terminator at the end of the logoffRPC characters in the buffer
        int valwrite = send(sock, buffer, strlen(buffer) + 1, 0); // Sends the contents of the buffer through the created socket

        printf("Disconnect message sent with %d bytes\n", valwrite);

        int valread = read(sock, buffer, 1024); // Assigns the server response to the buffer
        printf("Return response = %s with valread = %d\n", buffer, valread);
    }
    else
    {
        printf("Exit without calling RPC");
    }

    // Terminate connection
    close(sock);

    return 0;
}