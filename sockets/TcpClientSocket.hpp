#pragma once

#include "TcpSocket.hpp"

class TcpClientSocket : public TcpSocket {

public:

    TcpClientSocket(std::string host, std::string port)
            : TcpSocket(host, port)
    {
    }

    void openConnection()
    {
        // Connect to server, returning on failure
        if (connect(_sock, _addressInfo->ai_addr, (int)_addressInfo->ai_addrlen) == INVALID_SOCKET) {
            closeConnection(_sock);
            std::cerr << "connect() failed; please make sure server is running" << std::endl;
            return;
        }

        // For a client, the connection is the same as the main socket
        _conn = _sock;
    }

    bool safeSendData(void *buf, size_t len)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "safeSendData: No connection" << std::endl;
            return false;
        }

        if (!sendData(buf, len)) {
            closeConnections();
            return false;
        }
        return true;
    }

    bool safeReceiveData(void *buf, size_t len)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "safeReceiveData: No connection" << std::endl;
            return false;
        }

        if (!receiveData(buf, len)) {
            closeConnections();
            return false;
        }
        return true;
    }

    void closeConnections()
    {
        closeConnection(_sock);
        _conn = _sock;
    }

};
