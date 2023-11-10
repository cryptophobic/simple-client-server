#include "ServiceConnector.hpp"
#include <sstream>
#include <string>

namespace InvoiceMasterClient {

    void ServiceConnector::establishConnection()
    {
        if (!clientSocket.isConnected()) {
            clientSocket.openConnection();
        }
    }

    std::unique_ptr<Response> ServiceConnector::sendCommand(std::unique_ptr<Request> request)
    {
        std::string message, response;
        for(auto & chunk: request->getParsed()) {
            clientSocket.safeSendData(chunk);
        }
        do {
            clientSocket.safeReceiveData(message);
            std::cout << message << std::endl;
            response += message;
        } while (!message.empty() && message.back() != settings::terminateChar);
        if (!response.empty()) {
            response.pop_back();
        }
        return std::make_unique<Response>(response);
    }

    void ServiceConnector::closeConnection()
    {
        clientSocket.closeConnections();
    }

    bool ServiceConnector::isConnected() {
        return clientSocket.isConnected();
    }

} // InvoiceMasterClient
