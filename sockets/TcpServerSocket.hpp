#pragma once

#include "TcpSocket.hpp"
#include <iostream>
#include <sstream>

class TcpServerSocket : public TcpSocket {

public:

    TcpServerSocket(std::string host, std::string port)
            : TcpSocket(host, port)
    {
        // Bind socket to address
        if (bind(_sock, _addressInfo->ai_addr, (int)_addressInfo->ai_addrlen) == INVALID_SOCKET) {
            closesocket(_sock);
            std::cerr << "bind() failed" << std::endl;
            return;
        }
    }

    void acceptConnection()
    {
        // Listen for a connection, exiting on failure
        if (listen(_sock, 1)  == -1) {
            std::cerr << "listen() failed" << std::endl;
            return;
        }

        // Accept connection, exiting on failure
        std::cout << "Waiting for client to connect on " << _host << ":" << _port << std::endl;
        _conn = accept(_sock, nullptr, nullptr);
        if (_conn == INVALID_SOCKET) {
            std::cerr << "accept() failed" << std::endl;
            return;
        }
        std::cout << "connected" << std::endl;
    }

    bool safeSendData(void *buf, size_t len)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "safeSendData: No connection" << std::endl;
            return false;
        }

        if (!sendData(buf, len)) {
            closeConnection(_conn);
            return false;
        }
        return true;
    }

    bool safeReceiveData(void *buf, size_t len)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "No connection" << std::endl;
            return false;
        }

        if (!receiveData(buf, len)) {
            closeConnection(_conn);
            return false;
        }
        return true;
    }

    void closeConnections()
    {
        closeConnection(_conn);
        closeConnection(_sock);
    }
};
