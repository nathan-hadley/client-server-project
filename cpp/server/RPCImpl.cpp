#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

#include "RPCImpl.h"
#include "LocalContext.h"
using namespace std;

typedef struct GlobalContext {
    int g_rpcCount;
} GlobalContext;

GlobalContext globalObj; // We need to protect this, as we don't want bad data

RPCImpl::RPCImpl(int socket) {
    m_socket = socket;
    m_rpcCount = 0;
}

RPCImpl::~RPCImpl() = default;

/*
 * ParseTokens splits a string by semicolons and adds all strings to the input
 * vector.
 *
 * Input:
 *      buffer: The string to be split
 *      a: The vector to have strings added to
 */
void RPCImpl::ParseTokens(char* buffer, vector<string>& a) {
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
void RPCImpl::ProcessRPC() {
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
            ProcessDisconnectRPC();
            printf("Disconnected from client.\n\n");
            bContinue = false; // We are going to leave this loop

        } else {
            printf("Error: not an RPC.\n");
        }
        printf("Waiting.\n");
    }
}

/*
 * Processes the "connect" RPC. Returns true if login is valid.
 *
 * Input:
 *      - arrayTokens: tokens received from client (Ex.: "connect," "USERNAME,"
 *      and "PASSWORD1234."
 */
bool RPCImpl::ProcessConnectRPC(vector<string>& arrayTokens) const {
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
void RPCImpl::ProcessDisconnectRPC() const {
    char szBuffer[16];
    strcpy(szBuffer, "1;");

    // Send Response back on our socket
    int nlen = (int) strlen(szBuffer);
    szBuffer[nlen] = 0;
    send(this->m_socket, szBuffer, (int) strlen(szBuffer) + 1, 0);
}