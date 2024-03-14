#include "transport/TcpServerSocket.hpp"

namespace transport {

    TcpServerSocket::TcpServerSocket(const char *host, const char *port)
            : TcpSocket(host, port) {
    }

    void TcpServerSocket::acceptConnection() {
        if (_addressInfo == nullptr) {
            socketInit();
            // Bind socket to address
            if (bind(_sock, _addressInfo->ai_addr, (int) _addressInfo->ai_addrlen) == SOCKET_ERROR) {
                closeConnection(_sock);
                throw std::runtime_error("bind() failed");
            }
        }
        // Listen for a connection, exiting on failure
        if (listen(_sock, 1) == -1) {
            closeConnections();
            throw std::runtime_error("listen() failed");
        }

        // Accept connection, exiting on failure
        std::cout << "Waiting for InvoiceMasterClient to connect on " << _host << ":" << _port << std::endl;
        _conn = accept(_sock, nullptr, nullptr);
        if (_conn == SOCKET_ERROR) {
            _conn = INVALID_SOCKET;
            std::cerr << "accept() failed" << std::endl;
            return;
        }
        std::cout << "connected" << std::endl;
    }

    bool TcpServerSocket::safeSendData(std::string &message) {
        if (_conn == INVALID_SOCKET) {
            throw std::runtime_error("safeSendData: No connection");
        }
        if (sendData(static_cast<void *>(&message), message.length()) != message.length()) {
            closeConnection(_conn);
            return false;
        }
        return true;
    }

    bool TcpServerSocket::safeReceiveData(std::string &message) {
        if (_conn == INVALID_SOCKET) {
            throw std::runtime_error("safeSendData: No connection");
            return false;
        }
        char buf[TRANSPORT_BUFFER_LIMIT];

        if (auto length = receiveData(buf, TRANSPORT_BUFFER_LIMIT - 1); length > 0) {
            buf[length] = 0;
            message = buf;
            return true;
        }
        closeConnection(_conn);
        return false;
    }

    bool TcpServerSocket::isServerUp() {
        return _sock != INVALID_SOCKET;
    }

    void TcpServerSocket::closeConnections() {
        closeConnection(_conn);
        closeConnection(_sock);
    }
}
