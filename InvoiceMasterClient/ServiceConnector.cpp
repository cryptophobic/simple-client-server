#include "ServiceConnector.hpp"
#include <sstream>
#include <vector>
#include <string>

namespace InvoiceMasterClient {

    ServiceConnector::ServiceConnector() : clientSocket(settings::hostName, settings::port)
    {
    }

    void ServiceConnector::establishConnection()
    {
        if (!clientSocket.isConnected()) {
            clientSocket.openConnection();
        }
    }

    std::vector<std::string> ServiceConnector::prepareArguments(
            settings::ServiceSignature command,
            const std::vector<std::string> &arguments)
    {
        std::vector<std::string> chunks = {1, std::string{}};
        int i = 0;
        chunks[i] = command.code;
        if (arguments.size() != command.argumentsNumber) {
            //TODO: error
            return {};
        }
        int limit = TRANSPORT_BUFFER_LIMIT - 2;
        for (auto &argument: arguments) {
            chunks[i] += settings::delimiter;
            int positionStart = 0;
            while (limit < argument.length() - positionStart) {
                chunks[i] += argument.substr(positionStart, limit);
                i++;
                positionStart += limit;
                limit = TRANSPORT_BUFFER_LIMIT - 1;
                chunks.emplace_back("");
            }
            chunks[i] += argument.substr(positionStart, limit);
        }
        chunks[i] += settings::terminateChar;
        return chunks;
    }

    std::string ServiceConnector::sendCommand(settings::ServiceSignature command, const std::vector<std::string>& arguments)
    {
        std::vector<std::string> chunks = prepareArguments(command, arguments);
        std::string message;
        for(auto & chunk: chunks) {
            clientSocket.safeSendData(chunk);
            clientSocket.safeReceiveData(message);
            //TODO: validate
            if (message == "OK") {
                std::cout << "Chunk transferred successfully" << std::endl;
            }
        }
        clientSocket.safeReceiveData(message);
        return message;
        //processResponse(message);
    }

    void ServiceConnector::closeConnection()
    {
        clientSocket.closeConnections();
    }
} // InvoiceMasterClient
