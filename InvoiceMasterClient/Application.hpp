#pragma once

#include "ServiceConnector/ServiceConnector.hpp"
#include "ServiceConnector/Response.hpp"

namespace InvoiceMasterClient {

    class Application {
    public:
        void run();
    private:
        bool isAuthorised = false;
        ServiceConnector connector;
        std::unique_ptr<Response> controller(settings::ServiceSignature command);
        std::vector<std::string> login();
        char menu();
        bool quit = false;
    };
}
