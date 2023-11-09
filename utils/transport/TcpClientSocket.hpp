#pragma once

#include "TcpSocket.hpp"

class TcpClientSocket : public TcpSocket {

public:

    TcpClientSocket(const char * host, const char * port)
            : TcpSocket(host, port)
    {
    }

    void openConnection()
    {
        if (_addressInfo == nullptr) {
            socketInit();
        }
        // Connect to server, returning on failure
        if (connect(_sock, _addressInfo->ai_addr, (int)_addressInfo->ai_addrlen) == SOCKET_ERROR) {
            closeConnection(_sock);
            std::cerr << "connect() failed; please make sure server is running" << std::endl;
            return;
        }

        // For a InvoiceMasterClient, the connection is the same as the main socket
        _conn = _sock;
    }

    bool safeSendData(const std::string& message)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "safeSendData: No connection" << std::endl;
            return false;
        }

        if (sendData((void *)message.c_str(), message.length()) != message.length()) {
            closeConnections();
            return false;
        }
        return true;
    }

    bool safeReceiveData(std::string& message)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "safeReceiveData: No connection" << std::endl;
            return false;
        }

        char buf[100];

        if (auto length = receiveData(buf, 100); length > 0) {
            buf[length] = 0;
            message = buf;
            return true;
        }
        closeConnections();
        return false;
    }

    void closeConnections()
    {
        closeConnection(_sock);
        _conn = _sock;
    }
};
