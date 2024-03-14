#include <sstream>
#include <string>
#include "ServiceConnector.hpp"
#include "protocol/Agreements.hpp"

namespace InvoiceMasterClient {

    void ServiceConnector::establishConnection()
    {
        if (!clientSocket.isConnected()) {
            clientSocket.openConnection();
        }
    }

    std::unique_ptr<protocol::ResponseStructure> ServiceConnector::sendCommand(const std::string& request)
    {
        std::string response;
        if (!clientSocket.safeSendData(request)) {
            throw std::runtime_error("sendCommand: cannot send request");
        }
        if (!clientSocket.safeReceiveData(response)) {
            throw std::runtime_error("sendCommand: cannot receive data");
        }
        if (!response.empty()) {
            response.pop_back();
        }
        return protocol::Response::parse(response);
    }

    void ServiceConnector::closeConnection()
    {
        clientSocket.closeConnections();
    }

    bool ServiceConnector::isConnected()
    {
        return clientSocket.isConnected();
    }
} // InvoiceMasterClient
