#include "transport/TcpSocket.hpp"

namespace transport {

    bool TcpSocket::initWinsock(void) {
#ifdef _WIN32
        WSADATA wsaData;
            if (int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); iResult != 0) {
                std::cerr << "WSAStartup() failed with error: " << iResult << std::endl;
                return false;
            }
#endif
        return true;
    }

    void TcpSocket::cleanup(void) {
#ifdef _WIN32
        WSACleanup();
#endif
    }

    ssize_t TcpSocket::sendData(void *buf, size_t len) const {
        return send(_conn, buf, len, 0);
    }

    ssize_t TcpSocket::receiveData(void *buf, size_t len) const {
        return recv(_conn, buf, len, 0);
    }

    void TcpSocket::socketInit() {
        // Initialize Winsock, returning on failure
        if (!initWinsock()) return;

        // Set up InvoiceMasterClient address info
        struct addrinfo hints{};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        // Resolve the server address and port, returning on failure
        if (int iResult = getaddrinfo(_host.c_str(), _port.c_str(), &hints, &_addressInfo); iResult != 0) {
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

    void TcpSocket::closeConnection(SOCKET &socket) {
        if (socket == INVALID_SOCKET) return;
        closesocket(socket);
        socket = INVALID_SOCKET;
    }

    TcpSocket::TcpSocket(const char *host, const char *port) {
        if(host == nullptr || port == nullptr) {
            throw std::invalid_argument("Host and port of socket cannot be empty");
        }
        _host = host;
        _port = port;
    }

    TcpSocket::~TcpSocket() {
        freeaddrinfo(_addressInfo);
    }

    bool TcpSocket::isConnected() const {
        return _conn != INVALID_SOCKET;
    }
}
