//#include <ctime>
//#include <iostream>
//#include <unistd.h>
//
//#include "ValueResponse.hpp"
//#include "SynchronizeTime.hpp"
//#include "TcpConnection.hpp"

/// Main function to setup the connection, restart it periodically, read the data and forwards them to the decoder / serializer.
int main(int argc, char* argv[])
{
//    SynchronizeTime sync;
//
//    if (argc != 2) {
//        std::cout << std::endl << "Usage: " <<  argv[0] << " <ip of server>" << std::endl;
//        return 1;
//    }
//
//    TcpConnection tcpConnection(argv[1], 8889);
//    if (false == tcpConnection.connectToHeating()) {
//        return 2;
//    }
//
//    while(true)
//    {
//        std::time_t currentUnixTime = sync.waitForMinute();
//
//        std::cout << "------------------------------------------------------" << std::endl;
//        RecDataStoragePtr receiveDataPtr = tcpConnection.requestValues();
//
//        ValueResponse decodeValueResp(receiveDataPtr, currentUnixTime);
//        //decodeValueResp.decode();
//        decodeValueResp.serialize();
//        sleep(5);
//    }
//
//    tcpConnection.disconnectFromHeating();
    return 0;
}