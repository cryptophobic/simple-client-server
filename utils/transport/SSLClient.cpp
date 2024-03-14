#include "transport/SSLClient.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>

namespace transport {

    void SSLClient::createContext() {
        sslCtx = std::unique_ptr<SSL_CTX, decltype(&::SSL_CTX_free)>(SSL_CTX_new(TLS_client_method()), ::SSL_CTX_free);

        if (sslCtx == nullptr) {
            handleErrors();
        }

        if (SSL_CTX_set_min_proto_version(sslCtx.get(), TLS1_3_VERSION) != 1) {
            handleErrors();
        }
    }

    void SSLClient::configureContext() {
        /*
         * Configure the client to abort the handshake if certificate verification
         * fails
         */
        SSL_CTX_set_verify(sslCtx.get(), SSL_VERIFY_PEER, nullptr);
        /*
         * In a real application you would probably just use the default system certificate trust store and call:
         *     SSL_CTX_set_default_verify_paths(ctx);
         * In this demo though we are using a self-signed certificate, so the client must trust it directly.
         */
        if (SSL_CTX_load_verify_locations(sslCtx.get(), certPath.c_str(), nullptr) != 1) {
            handleErrors();
        }
    }

    void SSLClient::openConnection() {

        TcpClientSocket::openConnection();
        createContext();
        configureContext();

        /* Create client SSL structure using dedicated client socket */
        ssl = std::unique_ptr<SSL, decltype(&::SSL_free)>(SSL_new(sslCtx.get()), ::SSL_free);
        if (SSL_set_fd(ssl.get(), _conn) != 1) {
            handleErrors();
        }

        if (SSL_set_tlsext_host_name(ssl.get(), _host.c_str()) != 1) {
            handleErrors();
        }

        if (SSL_set1_host(ssl.get(), _host.c_str()) != 1) {
            handleErrors();
        }

        if (SSL_connect(ssl.get()) != 1) {
            handleErrors();
        }
    }

    bool SSLClient::safeReceiveData(std::string &message) {

        char buf[TRANSPORT_BUFFER_LIMIT];
        size_t length;
        int retries = SOCKET_RETRIES;
        do {
            if (SSL_read_ex(ssl.get(), buf, TRANSPORT_BUFFER_LIMIT, &length) > 0) {
                message = std::string {buf, static_cast<unsigned int>(length)};
                return true;
            }
            std::cerr << "No response, retry " << retries << std::endl;
        } while (retries-- > 0);

        closeConnections();
        return false;
    }

    bool SSLClient::safeSendData(const std::string &message) {

        if (SSL_write(ssl.get(), message.c_str(), message.length()) != message.length()) {
            closeConnections();
            return false;
        }
        return true;
    }

    void SSLClient::closeConnections() {
        if (ssl != nullptr) {
            SSL_shutdown(ssl.get());
        }
        TcpClientSocket::closeConnections();
    }

    void SSLClient::handleErrors() {
        auto errorCode = ERR_get_error();
        if (errorCode) {
            closeConnections();
            throw std::runtime_error(ERR_error_string(errorCode, nullptr));
        }
    }
} // transport
