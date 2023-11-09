#pragma once

#include "ServiceConnector.hpp"

namespace InvoiceMasterClient {

    class Application {
    public:
        void Run();
        ServiceConnector connector; // incapsulates utils transport business logic

        //login(user, password);

    };
}
