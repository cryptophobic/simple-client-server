#pragma once
#include "transport/TcpClientSocket.hpp"
#include "transport/SSLClient.hpp"
#include "config/settings.hpp"
#include "protocol/Response.hpp"
#include <string>
#include <vector>
#include <memory>

namespace InvoiceMasterClient {

    class ServiceConnector {
    protected:
        transport::SSLClient clientSocket;
    public:
        ServiceConnector() : clientSocket(settings::hostName, settings::port) {};
        bool isConnected();
        void establishConnection();
        std::unique_ptr<protocol::ResponseStructure> sendCommand(const std::string&);
        void closeConnection();
    };

} // InvoiceMasterClient
