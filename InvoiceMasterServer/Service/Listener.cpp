#include "Listener.hpp"

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

    std::unique_ptr<Request> Listener::receiveCommand() {
        std::string message, request;

        do {
            serverSocket.safeReceiveData(message);
            std::cout << message << std::endl;
            request += message;
        } while (!message.empty() && message.back() != settings::terminateChar);
        if (!request.empty()) {
            request.pop_back();
        }

        return std::make_unique<Request>(request);
    }

    void Listener::sendResponse(std::unique_ptr<Response> response) {
        for(auto & chunk: response->getParsed()) {
            serverSocket.safeSendData(chunk);
        }
    }

    bool Listener::isClientConnected() {
        return serverSocket.isConnected();
    }

} // InvoiceMasterServer
