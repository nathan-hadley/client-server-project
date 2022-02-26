#pragma once
class LocalContext
{
public:
    int getThreadRpCount() const { return threadRpcCount; }
private:
    int threadRpcCount;
};
