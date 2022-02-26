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

#include <cstdio>
#include "RPCServer.h"
using namespace std;

// Main function for the server.
int main(int argc, char const* argv[]) {

    const char* serverIP = argv[1];
    int port = atoi(argv[2]);

    auto* serverObj = new RPCServer(serverIP, port);

    serverObj->StartServer();
    printf("\nServer is running.\nWaiting.\n");
    serverObj->ListenForClient();

    delete serverObj;
    return 0;
}