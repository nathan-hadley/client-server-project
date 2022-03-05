#pragma once
#include <string>
#include <vector>
using namespace std;

class RPCImpl {
public:
    explicit RPCImpl(int socket);
    ~RPCImpl();
    void ProcessRPC();
private:
    int m_socket;

    bool ProcessConnectRPC(vector<string>& arrayTokens) const;
    void playConnect4RPC(vector<string>& arrayTokens);
    void playPieceRPC(vector<string>& arrayTokens) const;
    void checkStatsRPC() const;
    void ProcessDisconnectRPC() const;

    static void ParseTokens(char* buffer, vector<string>& a);

};