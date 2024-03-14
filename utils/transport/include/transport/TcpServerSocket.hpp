#pragma once

#include "TcpSocket.hpp"
#include <iostream>
#include <sstream>

namespace transport {

    class TcpServerSocket : public TcpSocket {

    public:

        TcpServerSocket(const char *host, const char *port);

        virtual void acceptConnection();
        virtual bool safeSendData(std::string &message);
        virtual bool safeReceiveData(std::string &message);
        virtual bool isServerUp();
        virtual void closeConnections();
    };
}