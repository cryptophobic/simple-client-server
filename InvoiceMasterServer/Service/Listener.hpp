#pragma once

#include "transport/TcpServerSocket.hpp"
#include "transport/SSLServer.hpp"
#include "config/settings.hpp"
#include <string>
#include <vector>

namespace InvoiceMasterServer {

    class Listener {
    protected:
        transport::SSLServer serverSocket;
    public:
        Listener() : serverSocket(settings::hostName, settings::port) {}
        void listen();
        bool isClientConnected();
        void read(std::string&);
        void sendResponse(std::string&);
    };

} // InvoiceMasterServer
