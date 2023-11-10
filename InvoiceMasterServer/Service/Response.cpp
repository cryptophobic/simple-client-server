#include "Response.hpp"
#include "../../utils/transport/TcpSocket.hpp"
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterServer {

    Response::Response(char responseCode, const std::string& responseBody) : _responseCode(responseCode), _responseBody(std::move(responseBody))
    {
    }

    std::vector<std::string> Response::getParsed()
    {
        std::vector<std::string> chunks = {1, std::string{}};
        int currentChunk = 0;
        int limit = TRANSPORT_BUFFER_LIMIT - 2;
        chunks[currentChunk] = _responseCode;
        chunks[currentChunk] += settings::delimiter;
        int positionStart = 0;

        while (limit < _responseBody.length() - positionStart) {
            chunks[currentChunk++] += _responseBody.substr(positionStart, limit);
            positionStart += limit;
            limit = TRANSPORT_BUFFER_LIMIT - 1;
            chunks.emplace_back("");
        }
        chunks[currentChunk] += _responseBody.substr(positionStart, limit);
        chunks[currentChunk] += settings::terminateChar;
        return chunks;
    }
} // InvoiceMasterServer
