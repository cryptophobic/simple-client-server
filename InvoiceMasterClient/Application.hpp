#pragma once

#include "ServiceConnector/ServiceConnector.hpp"
#include "Controller.hpp"
#include "BaseApplication.hpp"
#include <memory>

namespace InvoiceMasterClient {

    class Application : public BaseApplication, public std::enable_shared_from_this<Application> {
    public:
        void run();

    protected:
        ServiceConnector connector;
        std::unique_ptr<Controller> controller;
    };
}
