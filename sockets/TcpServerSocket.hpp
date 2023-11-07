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

    bool safeSendData(const std::string& message)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "safeSendData: No connection" << std::endl;
            return false;
        }
        if (sendData((void *)message.c_str(), message.length()) != message.length()) {
            closeConnection(_conn);
            return false;
        }
        return true;
    }

    bool safeReceiveData(std::string& message)
    {
        if (_conn == INVALID_SOCKET) {
            std::cerr << "No connection" << std::endl;
            return false;
        }
        char buf[100];

        if (auto length = receiveData(buf, 100); length > 0) {
            buf[length] = 0;
            message = buf;
            return true;
        }
        closeConnection(_conn);
        return false;
    }

    void closeConnections()
    {
        closeConnection(_conn);
        closeConnection(_sock);
    }
};
