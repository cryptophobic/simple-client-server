#include "transport/SSLServer.hpp"
#include <openssl/err.h>

namespace transport {

    void SSLServer::createContext() {
        sslCtx = std::unique_ptr<SSL_CTX, decltype(&::SSL_CTX_free)>(SSL_CTX_new(TLS_server_method()), ::SSL_CTX_free);

        if (sslCtx == nullptr) {
            handleErrors();
        }

        if (SSL_CTX_set_min_proto_version(sslCtx.get(), TLS1_3_VERSION) != 1) {
            handleErrors();
        }
    }

    void SSLServer::configureContext() {
        /* Set the key and cert */
        if (SSL_CTX_use_certificate_chain_file(sslCtx.get(), certPath.c_str()) != 1) {
            handleErrors();
        }

        if (SSL_CTX_use_PrivateKey_file(sslCtx.get(), keyPath.c_str(),SSL_FILETYPE_PEM) != 1) {
            handleErrors();
        }
    }

    void SSLServer::acceptConnection() {
        TcpServerSocket::acceptConnection();
        createContext();
        configureContext();

        ssl = std::unique_ptr<SSL, decltype(&::SSL_free)>(SSL_new(sslCtx.get()), ::SSL_free);
        SSL_set_fd(ssl.get(), _conn);

        if (SSL_accept(ssl.get()) <= 0) {
            closeConnections();
        }
    }

    bool SSLServer::safeSendData(std::string &message) {
        if (SSL_write(ssl.get(), message.c_str(), message.length()) <= 0) {
            closeConnection(_conn);
            return false;
        }
        return true;
    }

    bool SSLServer::safeReceiveData(std::string &message) {
        char buf[TRANSPORT_BUFFER_LIMIT];

        size_t length;
        if (SSL_read_ex(ssl.get(), buf, TRANSPORT_BUFFER_LIMIT, &length) != 1) {
            closeConnection(_conn);
            return false;
        }

        message = std::string (buf, length);

        return true;
    }

    void SSLServer::closeConnections() {
        if (ssl != nullptr) {
            SSL_shutdown(ssl.get());
        }
        TcpServerSocket::closeConnections();
    }

    void SSLServer::handleErrors() {
        auto errorCode = ERR_get_error();
        if (errorCode) {
            closeConnections();
            throw std::runtime_error(ERR_error_string(errorCode, nullptr));
        }
    }

} // transport
