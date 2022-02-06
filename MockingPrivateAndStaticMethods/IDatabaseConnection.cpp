#include "IDatabaseConnection.hpp"

#include <iostream>

IDatabaseConnection::IDatabaseConnection(std::string serverAddress, HelperClass* hC)
    : mServerAddress { serverAddress },
      mHelper { hC }
{
    hC->increaseConnectionCount();
}

void IDatabaseConnection::connect()
{
    std::cout << "Connecting to database server " << mServerAddress << "\n";
    // initialize real DB connection
    // if (mOnConnect != nullptr) {
    //     std::cout << "Callback was set!\n";
    //     mOnConnect(5, 6);
    // }
    onConnect();
}

void IDatabaseConnection::disconnect()
{
    std::cout << "Disconnecting from database\n";
    // close the real connection
}

void IDatabaseConnection::SetOnConnect(Callback onConnect)
{
    // mOnConnect = onConnect;
}

void IDatabaseConnection::increaseConnectionCount()
{
    connectionCount++;
}

unsigned IDatabaseConnection::connectionCount = 0;

void HelperClass::increaseConnectionCount()
{
    IDatabaseConnection::increaseConnectionCount();
}