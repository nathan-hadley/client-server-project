/* This is a very simple example of a server that will listen to a client
 * server, then run the various RPCs that between the server and client.
 *
 * Version 1 will have the server handle one client at a time. The server will:
 *      - Wait for connection from client
 *      - Process the Connect API once connected
 *      - Process all RPC requests until the client sends a disconnect RPC
 *      - This initial server will handle 2 RPC's:
 *          - Connect
 *          - Disconnect
*/

#pragma once
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <iterator>
using namespace std;


class RPCServer {
public:
    RPCServer(const char *serverIP, int port);
    ~RPCServer();
    bool StartServer();
    bool ListenForClient();
    bool ProcessRPC();
    static void ParseTokens(char* buffer, vector<string>& a);

private:
    int m_server_fd{};
    int m_socket{};
    char* m_serverIP;
    int m_port;
    struct sockaddr_in m_address{};

    // First one in this function should be a connect, and it will continue try
    // to process RPC's until a Disconnect happens.
    bool ProcessConnectRPC(vector<string>& arrayTokens) const;
    bool ProcessDisconnectRPC() const;
};
