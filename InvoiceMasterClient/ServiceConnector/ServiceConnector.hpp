#pragma once
#include "../../utils/transport/TcpSocket.hpp"
#include "../../utils/transport/TcpClientSocket.hpp"
#include "../../settings/ServiceList.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <string>
#include <vector>
#include <queue>
#include <memory>

namespace InvoiceMasterClient {

    class ServiceConnector {
    private:
        TcpClientSocket clientSocket;

    public:
        ServiceConnector() : clientSocket(settings::hostName, settings::port) {}
        bool isConnected();
        void establishConnection();
        std::unique_ptr<Response> sendCommand(std::unique_ptr<Request>);
        void closeConnection();
    };

} // InvoiceMasterClient
