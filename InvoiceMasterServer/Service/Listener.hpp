#pragma once

#include "../../utils/transport/TcpServerSocket.hpp"
#include "../../settings/ServiceList.hpp"
#include "Request.hpp"
#include "Response.hpp"

namespace InvoiceMasterServer {

    class Listener {
    private:
        TcpServerSocket serverSocket;
    public:
        Listener() : serverSocket(settings::hostName, settings::port) {}
        void listen();
        bool isClientConnected();
        std::unique_ptr<Request> receiveCommand();
        void sendResponse(std::unique_ptr<Response>);
    };

} // InvoiceMasterServer
