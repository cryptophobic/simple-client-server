#pragma once
#include "../utils/transport/TcpSocket.hpp"
#include "../utils/transport/TcpClientSocket.hpp"
#include "../settings/ServiceList.hpp"
#include <string>
#include <vector>
#include <queue>

namespace InvoiceMasterClient {

    class ServiceConnector {
    private:
        //std::queue<std::string> responseBuffer;
        TcpClientSocket clientSocket;
        static std::vector<std::string> prepareArguments(
                settings::ServiceSignature command,
                const std::vector<std::string>& arguments);

    public:
        ServiceConnector();
        void establishConnection();
        std::string sendCommand(settings::ServiceSignature command, const std::vector<std::string>& arguments);
        void closeConnection();
    };

} // InvoiceMasterClient
