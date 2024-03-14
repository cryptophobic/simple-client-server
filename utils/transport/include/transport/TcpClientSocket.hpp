#pragma once

#include "TcpSocket.hpp"

namespace transport {

    class TcpClientSocket : public TcpSocket {

    public:
        TcpClientSocket(const char *host, const char *port);

        virtual void openConnection();
        virtual bool safeSendData(const std::string &message);
        virtual bool safeReceiveData(std::string &message);
        virtual void closeConnections();
    };
}
