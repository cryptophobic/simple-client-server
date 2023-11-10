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
#ifdef _WIN32
        DWORD timeout = SOCKET_READ_TIMEOUT_SEC * 1000;
        setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
#else
        struct timeval timeout;
        timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC;
        timeout.tv_usec = 0;
        setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#endif

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
