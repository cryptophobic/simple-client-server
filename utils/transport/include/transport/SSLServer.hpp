#pragma once
#include "TcpServerSocket.hpp"
#include <openssl/ssl.h>

namespace transport {

    class SSLServer : public TcpServerSocket {
    protected:
        const std::string certPath = std::string(CERTIFICATE_DIR) + "/cert.pem";
        const std::string keyPath = std::string(CERTIFICATE_DIR) + "/key.pem";

        void handleErrors();
        void createContext();
        void configureContext();
        std::unique_ptr<SSL_CTX, decltype(&::SSL_CTX_free)> sslCtx{nullptr, nullptr};
        std::unique_ptr<SSL, decltype(&::SSL_free)> ssl{nullptr, nullptr};

    public:
        SSLServer(const char * host, const char * port): TcpServerSocket(host, port) {};

        void acceptConnection() override;
        bool safeSendData(std::string& message) override;
        bool safeReceiveData(std::string& message) override;
        void closeConnections() override;
    };

} // transport
