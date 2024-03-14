#include "Listener.hpp"
#include "protocol/Agreements.hpp"

namespace InvoiceMasterServer {
    void Listener::listen()
    {
        if (!serverSocket.isConnected()) {
            serverSocket.acceptConnection();
        }
        if (!serverSocket.isServerUp()) {
            throw std::runtime_error("Invalid bind server socket. Most probably port is in use.");
        }
    }

    void Listener::read(std::string &message)
    {
        std::string request;
        message.clear();
        message.reserve(TRANSPORT_BUFFER_LIMIT);
        do {
            serverSocket.safeReceiveData(request);
            message += request;
        } while (!request.empty() && request.back() != protocol::terminateChar);
        if (!message.empty()) {
            message.pop_back();
        }
    }

    void Listener::sendResponse(std::string& response)
    {
        serverSocket.safeSendData(response);
    }

    bool Listener::isClientConnected()
    {
        return serverSocket.isConnected();
    }

} // InvoiceMasterServer
