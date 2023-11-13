#pragma once

#include "ServiceConnector/ServiceConnector.hpp"
#include "ServiceConnector/Response.hpp"
#include "Controller.hpp"

namespace InvoiceMasterClient {

    class Application {
    public:
        static void run();
        static bool isAuthorized();
    private:
        static bool authorized;
        static ServiceConnector connector;
    };
}
