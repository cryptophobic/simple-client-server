#include "userInputOutput/Output.hpp"
#include <iostream>

namespace userInputOutput {
    void Output::formatResponse(const std::unique_ptr<protocol::ResponseStructure>& response)
    {
        if (response == nullptr) {
            return;
        }
        if(!response->body.empty()) {
            output_stream << response->body << std::endl;
        }
        output_stream << (response->responseCode != protocol::responseSuccess ? "[Failed!] " : "");
        output_stream << (response->connectionStatus != protocol::connected ? "Disconnected. " : "");
        output_stream << (response->authorized != protocol::authorized ? "Not authorized. " : "");
        output_stream << (response->licenceStatus == protocol::licenceNotConfirmed ? "Licence not confirmed! " : "");

        output_stream << std::endl;

    }

    void Output::outputLine(const std::string& text)
    {
        output_stream << text << std::endl;
    }

    void Output::output(const std::string& text)
    {
        output_stream << text;
    }
}
