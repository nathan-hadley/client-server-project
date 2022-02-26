//
// Created by Nathan Hadley on 2/26/22.
//

#ifndef SERVER_RPCIMPL_H
#define SERVER_RPCIMPL_H


#include <string>
#include <vector>
using namespace std;

class RPCImpl {
public:
    RPCImpl(int socket);
    ~RPCImpl();
    bool ProcessRPC();
private:
    int m_rpcCount;
    int m_socket;
    // First one in this function should be a connect, and it
    // will continue try to process RPC's until a Disconnect happens
    bool ProcessConnectRPC(vector<string>& arrayTokens) const;
    bool ProcessDisconnectRPC() const;
    static void ParseTokens(char* buffer, vector<string>& a);
};


#endif //SERVER_RPCIMPL_H
