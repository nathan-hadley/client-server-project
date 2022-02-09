#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <iterator>
#include "RPCServer.h"
using namespace std;

/*
 * Constructor for RPCServer
 * Input:
 *      serverIP: The IP of the server
 *      port: The port the server will be listening on
 */
RPCServer::RPCServer(const char* serverIP, int port) {
    m_serverIP = (char*)serverIP;
    m_port = port;
}

/*
 * Destructor
 */
RPCServer::~RPCServer() = default;

/*
 * StartServer will create a server on a port that was passed in, and create a
 * socket
 */
bool RPCServer::StartServer() {
    int opt = 1;
    const int BACKLOG = 10;

    // Creating socket file descriptor
    if ((m_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(m_port);

    // Forcefully attaching socket to the port
    if (bind(m_server_fd, (struct sockaddr*)&m_address,
        sizeof(m_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(m_server_fd, BACKLOG) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return true;
}

/*
 * Will accept a new connection by listening on its address
 */
bool RPCServer::ListenForClient() {

    int addrlen = sizeof(m_address);

    if ((m_socket = accept(m_server_fd, (struct sockaddr*)&m_address,
        (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    this->ProcessRPC();
    return true;
}

/*
 * ParseTokens splits a string by semicolons and adds all strings to the input
 * vector.
 *
 * Input:
 *      buffer: The string to be split
 *      a: The vector to have strings added to
 */
void RPCServer::ParseTokens(char* buffer, vector<string>& a) {
    char* token;
    char* rest = (char*)buffer;

    while ((token = strtok_r(rest, ";", &rest))) {
        a.emplace_back(token);
    }
}

/*
 * ProcessRPC will examine buffer and will essentially control the server
 * processes.
 */
bool RPCServer::ProcessRPC() {
    char buffer[1024] = { 0 };
    vector<string> arrayTokens;
    int valread;
    bool bConnected = false;
    const int RPC_TOKEN = 0;
    bool bContinue = true;

    while (bContinue) {
        // Should be blocked when a new RPC has not called us yet
        if ((valread = (int) read(this->m_socket, buffer, sizeof(buffer))) <= 0) {
            break;
        }

        arrayTokens.clear();
        this->ParseTokens(buffer, arrayTokens);

        // Enumerate through the tokens. The first token is always the RPC
        for (const auto& x : arrayTokens) {
            char* token = (char*)malloc(x.size() + 1);
            memcpy(token, x.c_str(), x.size() + 1);
            printf("Token received = %s\n", token);
            free(token);
        }

        // String statements are not supported with a switch, so using if/else
        // logic to dispatch.
        string aString = arrayTokens[RPC_TOKEN];

        if (!bConnected && (aString == "connect")) {
            bConnected = ProcessConnectRPC(arrayTokens);  // Connect RPC
        }

        else if (bConnected && (aString == "disconnect")) {
            bool statusOk = true;
            ProcessDisconnectRPC();
            printf("Disconnected from client.\n\n");
            bContinue = false; // We are going to leave this loop

        } else {
            printf("Error: not an RPC.\n");
        }
        printf("Waiting.\n");
    }
    return true;
}

/*
 * Processes the "connect" RPC. Returns true if login is valid.
 *
 * Input:
 *      - arrayTokens: tokens received from client (Ex.: "connect," "USERNAME,"
 *      and "PASSWORD1234."
 */
bool RPCServer::ProcessConnectRPC(vector<string>& arrayTokens) const {
    const int USERNAME_TOKEN = 1;
    const int PASSWORD_TOKEN = 2;
    bool validLogin;

    // Strip out tokens 1 and 2 (username, password)
    string usernameString = arrayTokens[USERNAME_TOKEN];
    string passwordString = arrayTokens[PASSWORD_TOKEN];
    char szBuffer[80];

    // Our authentication logic.
    if ((usernameString == "USERNAME") && (passwordString == "PASSWORD1234")) {
        strcpy(szBuffer, "1;"); // Connected
        validLogin = true;
        printf("Successful login.\n\n");
    } else {
        strcpy(szBuffer, "0;"); // Not connected
        validLogin = false;
        printf("Failed login.\n\n");
    }

    // Send Response back on our socket
    int nlen = (int) strlen(szBuffer);
    szBuffer[nlen] = 0;
    send(this->m_socket, szBuffer, (int) strlen(szBuffer) + 1, 0);

    if (validLogin) return true;
    else return false;
}

/*
 * Processes disconnectRPC.
*/
bool RPCServer::ProcessDisconnectRPC() const {
    char szBuffer[16];
    strcpy(szBuffer, "1;");

    // Send Response back on our socket
    int nlen = (int) strlen(szBuffer);
    szBuffer[nlen] = 0;
    send(this->m_socket, szBuffer, (int) strlen(szBuffer) + 1, 0);
    return true;
}