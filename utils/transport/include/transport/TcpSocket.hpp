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

#define TRANSPORT_BUFFER_LIMIT 10000
#define SOCKET_READ_TIMEOUT_SEC 60;
#define SOCKET_RETRIES 5;

namespace transport {

    class TcpSocket {

    protected:

        std::string _host;
        std::string _port;

        struct addrinfo *_addressInfo = nullptr;

        SOCKET _sock = INVALID_SOCKET;
        SOCKET _conn = INVALID_SOCKET;

        bool initWinsock();
        void cleanup();
        ssize_t sendData(void *buf, size_t len) const;
        ssize_t receiveData(void *buf, size_t len) const;
        void socketInit();
        static void closeConnection(SOCKET &socket);

    public:

        TcpSocket(const char *host, const char *port);
        ~TcpSocket();
        bool isConnected() const;
    };
}
