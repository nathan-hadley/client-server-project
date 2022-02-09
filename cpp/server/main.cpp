#include <cstdio>
#include "RPCServer.h"
using namespace std;

int main(int argc, char const* argv[]) {

    const char* serverIP = argv[1];
    int port = atoi(argv[2]);

    bool statusOk = true;
    auto* serverObj = new RPCServer(serverIP, port);

    statusOk = serverObj->StartServer();
    printf("\nServer is running.\nWaiting.\n");
    while (statusOk) {
        statusOk = serverObj->ListenForClient();
        statusOk = serverObj->ProcessRPC(); // Launch thread
    }

    delete serverObj;
    return 0;
}