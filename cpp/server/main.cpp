#include <cstdio>
#include "RPCServer.h"
using namespace std;

int main(int argc, char const* argv[]) {

    const char* serverIP = argv[1];
    int port = atoi(argv[2]);

    bool statusOk = true;
    auto* serverObj = new RPCServer(serverIP, port);

// Following code does nothing. Not sure how to make it useful.
// #if 0
//    vector<string> tokArray;
//    char buffer[128] = { "connect;mike;mike" };
//    serverObj->ParseTokens(buffer, tokArray);
// #endif

    // Print it out
    statusOk = serverObj->StartServer();
    printf("Endless loop, as server is up always\n");
    while (statusOk) {
        statusOk = serverObj->ListenForClient();
        statusOk = serverObj->ProcessRPC(); // Launch thread
    }

    delete serverObj;
    return 0;
}