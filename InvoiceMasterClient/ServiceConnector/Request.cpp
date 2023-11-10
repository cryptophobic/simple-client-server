//
// Created by Dmytro Uglach on 09.11.2023.
//

#include "Request.hpp"
#include "../../utils/transport/TcpSocket.hpp"

namespace InvoiceMasterClient {

    std::vector<std::string> Request::getParsed() {
        std::vector<std::string> chunks = {1, std::string{}};
        int currentChunk = 0;
        int limit = TRANSPORT_BUFFER_LIMIT - 2;
        chunks[currentChunk] = _command.code;
        if (_arguments.size() != _command.argumentsNumber) {
            //TODO: error
            return {};
        }
        for (auto &argument: _arguments) {
            chunks[currentChunk] += settings::delimiter;
            int positionStart = 0;
            while (limit < argument.length() - positionStart) {
                chunks[currentChunk++] += argument.substr(positionStart, limit);
                positionStart += limit;
                limit = TRANSPORT_BUFFER_LIMIT - 1;
                chunks.emplace_back("");
            }
            chunks[currentChunk] += argument.substr(positionStart, limit);
        }
        chunks[currentChunk] += settings::terminateChar;
        return chunks;
    }
}
