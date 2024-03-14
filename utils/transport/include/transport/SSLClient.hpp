#pragma once

#include "transport/TcpClientSocket.hpp"
#include <openssl/ssl.h>
#include <memory>

namespace transport {

    class SSLClient : public TcpClientSocket {
    protected:

        const std::string certPath = std::string(CERTIFICATE_DIR) + "/cert.pem";

        void handleErrors();
        void createContext();
        void configureContext();

        std::unique_ptr<SSL_CTX, decltype(&::SSL_CTX_free)> sslCtx{nullptr, nullptr};
        std::unique_ptr<SSL, decltype(&::SSL_free)> ssl{nullptr, nullptr};
    public:
        SSLClient(const char * host, const char * port): TcpClientSocket(host, port) {};
        void openConnection() override;
        bool safeSendData(const std::string& message) override;
        bool safeReceiveData(std::string& message) override;
        void closeConnections() override;
    };

} // transport