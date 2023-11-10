#pragma once

// Windows
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

// Linux
#else
typedef int SOCKET;
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR = -1;
#endif

#include <iostream>
#include <utility>

#ifndef _WIN32
static void closesocket(int socket) { close(socket); }
#endif

#define TRANSPORT_BUFFER_LIMIT 1000
#define SOCKET_READ_TIMEOUT_SEC 2;

class TcpSocket {

protected:

    std::string _host;
    std::string _port;

    struct addrinfo * _addressInfo = nullptr;

    SOCKET _sock = INVALID_SOCKET;
    SOCKET _conn = INVALID_SOCKET;

    bool initWinsock(void)
    {
#ifdef _WIN32
        WSADATA wsaData;
        if (int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); iResult != 0) {
            std::cerr << "WSAStartup() failed with error: " << iResult << std::endl;
            return false;
        }
#endif
        return true;
    }

    void cleanup(void)
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }

    size_t sendData(void *buf, size_t len) const
    {
        return (size_t)send(_conn, (const char *)buf, len, 0);
    }

    size_t receiveData(void *buf, size_t len) const
    {
        return (size_t)recv(_conn, (char *)buf, len, 0);
    }

    void socketInit()
    {
        // Initialize Winsock, returning on failure
        if (!initWinsock()) return;

        // Set up InvoiceMasterClient address info
        struct addrinfo hints{};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        // Resolve the server address and port, returning on failure
        if (int iResult = getaddrinfo(_host.c_str(), _port.c_str(), &hints, &_addressInfo); iResult != 0 ) {
            std::cerr << "getaddrinfo() failed with error: " << iResult;
            cleanup();
            return;
        }

        // Create a SOCKET for connecting to server, returning on failure
        _sock = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
        if (_sock == INVALID_SOCKET) {
            std::cerr << "socket() failed" << std::endl;
            cleanup();
            return;
        }
    }

    static void closeConnection(SOCKET &socket)
    {
        if (socket == INVALID_SOCKET) return;
        std::cout << "Disconnected " << socket << std::endl;
        closesocket(socket);
        socket = INVALID_SOCKET;
    }

public:

    TcpSocket(const char* host, const char* port) : _host(host), _port(port)
    {}

    ~TcpSocket() {
        freeaddrinfo(_addressInfo);
    }

    bool isConnected() const
    {
        return _conn != INVALID_SOCKET;
    }
};
