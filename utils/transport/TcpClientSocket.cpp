#include "transport/TcpClientSocket.hpp"

namespace transport {

    TcpClientSocket::TcpClientSocket(const char *host, const char *port)
            : TcpSocket(host, port) {
    }

    void TcpClientSocket::openConnection() {
        if (_addressInfo == nullptr) {
            socketInit();
        }
        // Connect to server, returning on failure
        if (connect(_sock, _addressInfo->ai_addr, (int) _addressInfo->ai_addrlen) == SOCKET_ERROR) {
            closeConnection(_sock);
            throw std::runtime_error("connect() failed; please make sure server is running");
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

    bool TcpClientSocket::safeSendData(const std::string &message) {
        if (_conn == INVALID_SOCKET) {
            throw std::runtime_error("safeSendData: No connection");
        }

        if (sendData((void *) message.c_str(), message.length()) != message.length()) {
            closeConnections();
            return false;
        }
        return true;
    }

    bool TcpClientSocket::safeReceiveData(std::string &message) {
        if (_conn == INVALID_SOCKET) {
            throw std::runtime_error("safeReceiveData: No connection");
        }

        char buf[TRANSPORT_BUFFER_LIMIT];
        int retries = SOCKET_RETRIES;
        do {
            if (auto length = receiveData(buf, TRANSPORT_BUFFER_LIMIT); length > 0) {
                message = std::string{buf, static_cast<unsigned int>(length)};
                return true;
            } else if (retries > 0) {
                std::cerr << "No response, retry " << retries <<  std::endl;
            }
        } while (retries-- > 0);

        closeConnections();
        return false;
    }

    void TcpClientSocket::closeConnections() {
        closeConnection(_sock);
        _conn = _sock;
    }
}
